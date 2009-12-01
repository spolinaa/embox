/**
 * @file if_ether.h
 *
 * @date 11.03.2009
 * @author Anton Bondarev
 * @brief Global definitions for the Ethernet IEEE 802.3 interface.
 */

#ifndef IF_ETHER_H_
#define IF_ETHER_H_

#define ETH_ALEN        6                        /* Octets in one ethernet addr */

/**
 * These are the defined Ethernet Protocol ID's.
 */
#define ETH_P_LOOP      (unsigned short)0x0060   /* Ethernet Loopback packet  */
#define ETH_P_IP        (unsigned short)0x0800   /* Internet Protocol packet  */
#define ETH_P_ARP       (unsigned short)0x0806   /* Address Resolution packet */

/**
 * This is an Ethernet frame header.
 */
typedef struct ethhdr {
	unsigned char h_dest[ETH_ALEN];       /**< destination eth addr */
	unsigned char h_source[ETH_ALEN];     /**< source ether addr    */
	__be16 h_proto;                       /**< packet type ID field */
} __attribute__((packed)) ethhdr_t;

#define ETH_HEADER_SIZE (sizeof(struct ethhdr))

#include "net/skbuff.h"

/**
 * extract MAC header for sbk
 * @param skb
 * @return pointer to MAC header
 */
static inline struct ethhdr *eth_hdr(const struct sk_buff *skb) {
        return (struct ethhdr*)skb->mac.raw;
}

#endif /* IF_ETHER_H_ */
