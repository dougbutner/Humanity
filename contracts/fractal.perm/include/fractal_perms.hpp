#pragma once

#include <eosio/action.hpp>
#include <eosio/binary_extension.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

#include <algorithm>
#include <cstdint>
#include <vector>

namespace fractal {

using eosio::check;
using eosio::name;
using eosio::permission_level;

struct permission_level_weight {
   permission_level permission;
   uint16_t         weight;
};

struct key_weight {
   eosio::public_key key;
   uint16_t          weight;
};

struct wait_weight {
   uint32_t wait_sec;
   uint16_t weight;
};

struct authority {
   uint32_t                           threshold = 0;
   std::vector<key_weight>            keys;
   std::vector<permission_level_weight> accounts;
   std::vector<wait_weight>           waits;
};

inline void sort_authority_accounts( authority& auth ) {
   std::sort( auth.accounts.begin(), auth.accounts.end(), []( const auto& a, const auto& b ) {
      if( a.permission.actor.value != b.permission.actor.value )
         return a.permission.actor.value < b.permission.actor.value;
      return a.permission.permission.value < b.permission.permission.value;
   } );
}

inline uint32_t total_account_weight( const authority& auth ) {
   uint32_t total = 0;
   for( const auto& a : auth.accounts )
      total += a.weight;
   for( const auto& k : auth.keys )
      total += k.weight;
   for( const auto& w : auth.waits )
      total += w.weight;
   return total;
}

inline authority make_account_authority( const std::vector<name>& winners,
                                         const std::vector<uint16_t>& weights,
                                         uint32_t threshold ) {
   check( winners.size() == weights.size(), "winners and weights size mismatch" );
   check( !winners.empty(), "winners required" );
   authority auth;
   auth.threshold = threshold;
   for( size_t i = 0; i < winners.size(); ++i ) {
      check( weights[i] >= 1, "weight must be at least 1" );
      auth.accounts.push_back( permission_level_weight{ permission_level{ winners[i], "active"_n }, weights[i] } );
   }
   sort_authority_accounts( auth );
   for( size_t i = 1; i < auth.accounts.size(); ++i ) {
      check( auth.accounts[i - 1].permission.actor != auth.accounts[i].permission.actor ||
                auth.accounts[i - 1].permission.permission != auth.accounts[i].permission.permission,
             "duplicate authority account" );
   }
   const uint32_t total = total_account_weight( auth );
   check( threshold >= 1, "threshold must be at least 1" );
   check( threshold <= total, "threshold exceeds total weight" );
   return auth;
}

inline void send_updateauth( const name& payer_perm_actor,
                             const name& payer_perm_name,
                             const name& account,
                             const name& permission,
                             const name& parent,
                             const authority& auth ) {
   action( permission_level{ payer_perm_actor, payer_perm_name },
           "ra"_n,
           "updateauth"_n,
           std::make_tuple( account, permission, parent, auth, eosio::binary_extension<name>{} ) )
       .send();
}

inline void send_setepoch( const name& payer_perm_actor,
                           const name& payer_perm_name,
                           const name& account,
                           const name& permission,
                           uint32_t period_sec,
                           uint16_t step,
                           uint32_t start_sec ) {
   action( permission_level{ payer_perm_actor, payer_perm_name },
           "ra"_n,
           "setepoch"_n,
           std::make_tuple( account, permission, period_sec, step, start_sec, eosio::binary_extension<name>{} ) )
       .send();
}

/**
 * Contract surface for election rotation, threshold adjust, and epoch configuration.
 * Epoch clock lives on the permission in core; this contract does not store a second clock.
 */
class [[eosio::contract("fractal.perm")]] fractal_perms : public eosio::contract {
  public:
   using contract::contract;

   // === Election Rotation === //
   [[eosio::action]]
   void setelection( const name& target,
                     const name& perm,
                     const name& parent,
                     const std::vector<name>& winners,
                     const std::vector<uint16_t>& weights,
                     uint32_t threshold,
                     uint32_t period_sec,
                     uint16_t step );

   // === Threshold Adjust === //
   // Rebuilds the authority with the same signers; applies integer delta to threshold.
   [[eosio::action]]
   void adjthreshold( const name& target,
                      const name& perm,
                      const name& parent,
                      const std::vector<name>& winners,
                      const std::vector<uint16_t>& weights,
                      uint32_t threshold,
                      int32_t delta );

   // === Epoch Config === //
   [[eosio::action]]
   void setdecay( const name& target,
                  const name& perm,
                  const name& parent,
                  uint32_t period_sec,
                  uint16_t step,
                  uint32_t start_sec );

   using setelection_action = eosio::action_wrapper<"setelection"_n, &fractal_perms::setelection>;
   using adjthreshold_action = eosio::action_wrapper<"adjthreshold"_n, &fractal_perms::adjthreshold>;
   using setdecay_action = eosio::action_wrapper<"setdecay"_n, &fractal_perms::setdecay>;
};

} // namespace fractal
