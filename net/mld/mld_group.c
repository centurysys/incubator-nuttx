/****************************************************************************
 * net/mld/mld_group.c
 * MLD group data structure management logic
 *
 *   Copyright (C) 2018 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of CITEL Technologies Ltd nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY CITEL TECHNOLOGIES AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CITEL TECHNOLOGIES OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <debug.h>

#include <arch/irq.h>

#include <nuttx/arch.h>
#include <nuttx/wdog.h>
#include <nuttx/kmalloc.h>
#include <nuttx/semaphore.h>
#include <nuttx/net/net.h>
#include <nuttx/net/netdev.h>
#include <nuttx/net/ip.h>
#include <nuttx/net/mld.h>

#include "devif/devif.h"
#include "mld/mld.h"

#ifdef CONFIG_NET_MLD

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name:  mld_grpalloc
 *
 * Description:
 *   Allocate a new group from heap memory.
 *
 * Assumptions:
 *   The network is locked.
 *
 ****************************************************************************/

FAR struct mld_group_s *mld_grpalloc(FAR struct net_driver_s *dev,
                                     FAR const net_ipv6addr_t addr)
{
  FAR struct mld_group_s *group;

  mldinfo("addr: %08x dev: %p\n", *addr, dev);
  group = (FAR struct mld_group_s *)kmm_zalloc(sizeof(struct mld_group_s));

  mldinfo("group: %p\n", group);

  /* Check if we successfully allocated a group structure */

  if (group != NULL)
    {
      /* Initialize the non-zero elements of the group structure */

      net_ipv6addr_copy(group->grpaddr, addr);

      /* This semaphore is used for signaling and, hence, should not have
       * priority inheritance enabled.
       */

      nxsem_init(&group->sem, 0, 0);
      nxsem_setprotocol(&group->sem, SEM_PRIO_NONE);

      /* Initialize the group timers */

      group->polldog = wd_create();
      DEBUGASSERT(group->polldog != NULL);
      if (group->polldog == NULL)
        {
          goto errout_with_sem;
        }

      group->v1dog = wd_create();
      DEBUGASSERT(group->v1dog != NULL);
      if (group->v1dog == NULL)
        {
          goto errout_with_polldog;
        }

      /* Save the interface index */

      group->ifindex = dev->d_ifindex;

      /* All routers start up as a Querier on each of their attached links. */

      SET_MLD_QUERIER(group->flags);

      /* Add the group structure to the list in the device structure */

      sq_addfirst((FAR sq_entry_t *)group, &dev->d_mld_grplist);
    }

  return group;

errout_with_polldog:
  wd_delete(group->polldog);

errout_with_sem:
  (void)nxsem_destroy(&group->sem);
  kmm_free(group);
  return NULL;
}

/****************************************************************************
 * Name:  mld_grpfind
 *
 * Description:
 *   Find an existing group.
 *
 * Assumptions:
 *   The network is locked.
 *
 ****************************************************************************/

FAR struct mld_group_s *mld_grpfind(FAR struct net_driver_s *dev,
                                    FAR const net_ipv6addr_t addr)
{
  FAR struct mld_group_s *group;

  mldinfo("Searching for addr %08x\n", (int)*addr);

  for (group = (FAR struct mld_group_s *)dev->d_mld_grplist.head;
       group;
       group = group->next)
    {
      mldinfo("Compare: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
              group->grpaddr[0], group->grpaddr[1], group->grpaddr[2],
              group->grpaddr[3], group->grpaddr[4], group->grpaddr[5],
              group->grpaddr[6], group->grpaddr[7]);
      mldinfo("Versus:  %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
              addr[0], addr[1], addr[2], addr[3],
              addr[4], addr[5], addr[6], addr[7]);

      if (net_ipv6addr_cmp(group->grpaddr, addr))
        {
          mldinfo("Match!\n");
          DEBUGASSERT(group->ifindex == dev->d_ifindex);
          break;
        }
    }

  return group;
}

/****************************************************************************
 * Name:  mld_grpallocfind
 *
 * Description:
 *   Find an existing group.  If not found, create a new group for the
 *   address.
 *
 ****************************************************************************/

FAR struct mld_group_s *mld_grpallocfind(FAR struct net_driver_s *dev,
                                         FAR const net_ipv6addr_t addr)
{
  FAR struct mld_group_s *group = mld_grpfind(dev, addr);

  mldinfo("group: %p addr: %08x\n", group, (int)*addr);
  if (!group)
    {
      group = mld_grpalloc(dev, addr);
    }

  mldinfo("group: %p\n", group);
  return group;
}

/****************************************************************************
 * Name:  mld_grpfree
 *
 * Description:
 *   Release a previously allocated group.
 *
 * Assumptions:
 *   The network is locked.
 *
 ****************************************************************************/

void mld_grpfree(FAR struct net_driver_s *dev, FAR struct mld_group_s *group)
{
  mldinfo("Free: %p flags: %02x\n", group, group->flags);

  /* Cancel the timers */

  wd_cancel(group->polldog);
  wd_cancel(group->v1dog);

  /* Remove the group structure from the group list in the device structure */

  sq_rem((FAR sq_entry_t *)group, &dev->d_mld_grplist);

  /* Destroy the wait semaphore */

  (void)nxsem_destroy(&group->sem);

  /* Destroy the timers */

  wd_delete(group->polldog);
  wd_delete(group->v1dog);

  /* Then release the group structure resources. */

  mldinfo("Call sched_kfree()\n");
  kmm_free(group);
}

#endif /* CONFIG_NET_MLD */
