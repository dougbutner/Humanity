#pragma once

#include <eosio/chain/authority.hpp>
#include <eosio/chain/types.hpp>

#include <algorithm>
#include <cstdint>

namespace eosio { namespace chain {

/**
 * Epoch decay attached to a permission. period_sec == 0 means decay is off.
 * Each completed period subtracts `step` from every factor weight. The stored
 * threshold is never changed by decay.
 */
struct auth_epoch {
   uint32_t period_sec = 0;
   uint16_t step       = 0;
   uint32_t start_sec  = 0;
};

inline uint32_t epoch_count( const auth_epoch& epoch, uint32_t now_sec ) {
   if( epoch.period_sec == 0 || now_sec <= epoch.start_sec )
      return 0;
   return ( now_sec - epoch.start_sec ) / epoch.period_sec;
}

inline uint16_t effective_weight( uint16_t weight, uint32_t epochs, uint16_t step ) {
   const uint64_t reduction = static_cast<uint64_t>( epochs ) * static_cast<uint64_t>( step );
   if( reduction >= weight )
      return 0;
   return static_cast<uint16_t>( weight - reduction );
}

/** Copy authority with factor weights reduced by completed epochs. Threshold unchanged. */
inline authority apply_epoch_decay( const authority& auth, const auth_epoch& epoch, uint32_t now_sec ) {
   authority out = auth;
   const uint32_t epochs = epoch_count( epoch, now_sec );
   if( epochs == 0 || epoch.step == 0 )
      return out;

   for( auto& k : out.keys )
      k.weight = effective_weight( k.weight, epochs, epoch.step );
   for( auto& a : out.accounts )
      a.weight = effective_weight( a.weight, epochs, epoch.step );
   for( auto& w : out.waits )
      w.weight = effective_weight( w.weight, epochs, epoch.step );
   return out;
}

inline authority apply_epoch_decay( const shared_authority& auth, const auth_epoch& epoch, uint32_t now_sec ) {
   return apply_epoch_decay( auth.to_authority(), epoch, now_sec );
}

/** True when no combination of remaining factors can meet the stored threshold. */
inline bool authority_unreachable( const authority& decayed ) {
   uint64_t total = 0;
   for( const auto& k : decayed.keys )
      total += k.weight;
   for( const auto& a : decayed.accounts )
      total += a.weight;
   for( const auto& w : decayed.waits )
      total += w.weight;
   return total < decayed.threshold;
}

} } // namespace eosio::chain

FC_REFLECT( eosio::chain::auth_epoch, (period_sec)(step)(start_sec) )
