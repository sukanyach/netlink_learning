#include <linux/netlink.h>
#include <linux/module.h>

#define NETLINK_SAMPLE 30

static struct sock nlsock;

static void nlmsg_dump(struct nlmsghdr *nlh);
#if 0 // For my reference
struct nlmsghdr {
        __u32           nlmsg_len;      /* Length of message including header */
        __u16           nlmsg_type;     /* Message content */
        __u16           nlmsg_flags;    /* Additional flags */
        __u32           nlmsg_seq;      /* Sequence number */
        __u32           nlmsg_pid;      /* Sending process port ID */
};
#endif

static void nlmsg_dump (struct nlmsghdr *nlh){
  printk(KERN_INFO "Dumping netlink Msgs Hdr");
  printk(KERN_INFO "netlink message length = %d\n", nlh->nlmsg_len);
  printk(KERN_INFO "netlink message type = %d\n", nlh->nlmsg_type);
  printk(KERN_INFO "netlink message flags = %d\n", nlh->nlmsg_flags);
  printk(KERN_INFO "netlink message seq number = %d\n", nlh->nlmsg_seq);
  printk(KERN_INFO "netlink message process port id = %d\n", nlh->nlmsg_pid);
}

static struct netlink_kernel_cfg cfg =  {
  .input = nlmsg_dump,
 };
static int __init netlink_sample_init(void)
{
  printk(KERN_INFO"In %s\n", __func__);
  nlsock = netlink_kernel_create(&init_net, NETLINK_SAMPLE, &cfg);  
}

void __exit netlink_sample_exit(void)
{
  printk(KERN_INFO"Exit from %s\n", __func__);
  netlink_kernel_release(nlsock);
  nlsock = NULL;
}
module_init(netlink_sample_init);
module_exit(netlink_sample_exit);
MODULE_LICENSE("GPL");
