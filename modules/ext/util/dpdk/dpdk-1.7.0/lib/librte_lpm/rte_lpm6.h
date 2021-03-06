/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2014 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _RTE_LPM6_H_
#define _RTE_LPM6_H_

/**
 * @file
 * RTE Longest Prefix Match for IPv6 (LPM6)
 */

#ifdef __cplusplus
extern "C" {
#endif


#define RTE_LPM6_MAX_DEPTH               128
#define RTE_LPM6_IPV6_ADDR_SIZE           16
/** Max number of characters in LPM name. */
#define RTE_LPM6_NAMESIZE                 32

#ifdef RTE_LIBRW_PIOT
#define RTE_LPM6_TBL24_NUM_ENTRIES        (1 << 24)
#define RTE_LPM6_TBL8_GROUP_NUM_ENTRIES         256
#define RTE_LPM6_TBL8_MAX_NUM_GROUPS      (1 << 21)

#define RTE_LPM6_VALID_EXT_ENTRY_BITMASK 0xA0000000
#define RTE_LPM6_LOOKUP_SUCCESS          0x20000000
#define RTE_LPM6_TBL8_BITMASK            0x001FFFFF

#define ADD_FIRST_BYTE                            3
#define LOOKUP_FIRST_BYTE                         4
#define BYTE_SIZE                                 8
#define BYTES2_SIZE                              16

#define lpm6_tbl8_gindex next_hop
  /** Tbl entry structure. It is the same for both tbl24 and tbl8 */
struct rte_lpm6_tbl_entry {
	uint32_t next_hop:	21;  /**< Next hop / next table to be checked. */
	uint32_t depth	:8;      /**< Rule depth. */

	/* Flags. */
	uint32_t valid     :1;   /**< Validation flag. */
	uint32_t valid_group :1; /**< Group validation flag. */
	uint32_t ext_entry :1;   /**< External entry. */
};

  /** Rules tbl entry structure. */
struct rte_lpm6_rule {
	uint8_t ip[RTE_LPM6_IPV6_ADDR_SIZE]; /**< Rule IP address. */
	uint8_t next_hop; /**< Rule next hop. */
	uint8_t depth; /**< Rule depth. */
};

  /** LPM6 structure. */
struct rte_lpm6 {
	/* LPM metadata. */
	char name[RTE_LPM6_NAMESIZE];    /**< Name of the lpm. */
	uint32_t max_rules;              /**< Max number of rules. */
	uint32_t used_rules;             /**< Used rules so far. */
	uint32_t number_tbl8s;           /**< Number of tbl8s to allocate. */
	uint32_t next_tbl8;              /**< Next tbl8 to be used. */

	/* LPM Tables. */
	struct rte_lpm6_rule *rules_tbl; /**< LPM rules. */
	struct rte_lpm6_tbl_entry tbl24[RTE_LPM6_TBL24_NUM_ENTRIES]
			__rte_cache_aligned; /**< LPM tbl24 table. */
	struct rte_lpm6_tbl_entry tbl8[0]
			__rte_cache_aligned; /**< LPM tbl8 table. */
};
#else
/** LPM structure. */
struct rte_lpm6;
#endif
  
/** LPM configuration structure. */
struct rte_lpm6_config {
	uint32_t max_rules;      /**< Max number of rules. */
	uint32_t number_tbl8s;   /**< Number of tbl8s to allocate. */
	int flags;               /**< This field is currently unused. */
};

/**
 * Create an LPM object.
 *
 * @param name
 *   LPM object name
 * @param socket_id
 *   NUMA socket ID for LPM table memory allocation
 * @param config
 *   Structure containing the configuration
 * @return
 *   Handle to LPM object on success, NULL otherwise with rte_errno set
 *   to an appropriate values. Possible rte_errno values include:
 *    - E_RTE_NO_CONFIG - function could not get pointer to rte_config structure
 *    - E_RTE_SECONDARY - function was called from a secondary process instance
 *    - E_RTE_NO_TAILQ - no tailq list could be got for the lpm object list
 *    - EINVAL - invalid parameter passed to function
 *    - ENOSPC - the maximum number of memzones has already been allocated
 *    - EEXIST - a memzone with the same name already exists
 *    - ENOMEM - no appropriate memory area found in which to create memzone
 */
struct rte_lpm6 *
rte_lpm6_create(const char *name, int socket_id,
		const struct rte_lpm6_config *config);

/**
 * Find an existing LPM object and return a pointer to it.
 *
 * @param name
 *   Name of the lpm object as passed to rte_lpm6_create()
 * @return
 *   Pointer to lpm object or NULL if object not found with rte_errno
 *   set appropriately. Possible rte_errno values include:
 *    - ENOENT - required entry not available to return.
 */
struct rte_lpm6 *
rte_lpm6_find_existing(const char *name);

/**
 * Free an LPM object.
 *
 * @param lpm
 *   LPM object handle
 * @return
 *   None
 */
void
rte_lpm6_free(struct rte_lpm6 *lpm);

/**
 * Add a rule to the LPM table.
 *
 * @param lpm
 *   LPM object handle
 * @param ip
 *   IP of the rule to be added to the LPM table
 * @param depth
 *   Depth of the rule to be added to the LPM table
 * @param next_hop
 *   Next hop of the rule to be added to the LPM table
 * @return
 *   0 on success, negative value otherwise
 */
int
rte_lpm6_add(struct rte_lpm6 *lpm, uint8_t *ip, uint8_t depth,
		uint8_t next_hop);

/**
 * Check if a rule is present in the LPM table,
 * and provide its next hop if it is.
 *
 * @param lpm
 *   LPM object handle
 * @param ip
 *   IP of the rule to be searched
 * @param depth
 *   Depth of the rule to searched
 * @param next_hop
 *   Next hop of the rule (valid only if it is found)
 * @return
 *   1 if the rule exists, 0 if it does not, a negative value on failure
 */
int
rte_lpm6_is_rule_present(struct rte_lpm6 *lpm, uint8_t *ip, uint8_t depth,
uint8_t *next_hop);

/**
 * Delete a rule from the LPM table.
 *
 * @param lpm
 *   LPM object handle
 * @param ip
 *   IP of the rule to be deleted from the LPM table
 * @param depth
 *   Depth of the rule to be deleted from the LPM table
 * @return
 *   0 on success, negative value otherwise
 */
int
rte_lpm6_delete(struct rte_lpm6 *lpm, uint8_t *ip, uint8_t depth);

/**
 * Delete a rule from the LPM table.
 *
 * @param lpm
 *   LPM object handle
 * @param ips
 *   Array of IPs to be deleted from the LPM table
 * @param depths
 *   Array of depths of the rules to be deleted from the LPM table
 * @param n
 *   Number of rules to be deleted from the LPM table
 * @return
 *   0 on success, negative value otherwise.
 */
int
rte_lpm6_delete_bulk_func(struct rte_lpm6 *lpm,
		uint8_t ips[][RTE_LPM6_IPV6_ADDR_SIZE], uint8_t *depths, unsigned n);

/**
 * Delete all rules from the LPM table.
 *
 * @param lpm
 *   LPM object handle
 */
void
rte_lpm6_delete_all(struct rte_lpm6 *lpm);

/**
 * Lookup an IP into the LPM table.
 *
 * @param lpm
 *   LPM object handle
 * @param ip
 *   IP to be looked up in the LPM table
 * @param next_hop
 *   Next hop of the most specific rule found for IP (valid on lookup hit only)
 * @return
 *   -EINVAL for incorrect arguments, -ENOENT on lookup miss, 0 on lookup hit
 */
int
rte_lpm6_lookup(const struct rte_lpm6 *lpm, uint8_t *ip, uint8_t *next_hop);

/**
 * Lookup multiple IP addresses in an LPM table.
 *
 * @param lpm
 *   LPM object handle
 * @param ips
 *   Array of IPs to be looked up in the LPM table
 * @param next_hops
 *   Next hop of the most specific rule found for IP (valid on lookup hit only).
 *   This is an array of two byte values. The next hop will be stored on
 *   each position on success; otherwise the position will be set to -1.
 * @param n
 *   Number of elements in ips (and next_hops) array to lookup.
 *  @return
 *   -EINVAL for incorrect arguments, otherwise 0
 */
int
rte_lpm6_lookup_bulk_func(const struct rte_lpm6 *lpm,
		uint8_t ips[][RTE_LPM6_IPV6_ADDR_SIZE],
		int16_t * next_hops, unsigned n);

#ifdef __cplusplus
}
#endif

#endif
