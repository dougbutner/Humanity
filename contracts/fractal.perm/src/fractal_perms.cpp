#include <fractal_perms.hpp>

#include <eosio/binary_extension.hpp>

namespace fractal {

// === Election Rotation === //
// --- Overwrite child permission and attach epoch decay --- //
void fractal_perms::setelection( const name& target,
                                 const name& perm,
                                 const name& parent,
                                 const std::vector<name>& winners,
                                 const std::vector<uint16_t>& weights,
                                 uint32_t threshold,
                                 uint32_t period_sec,
                                 uint16_t step ) {
   require_auth( get_self() );

   check( is_account( target ), "target account does not exist" );
   check( perm != "owner"_n && perm != "active"_n, "cannot replace owner or active" );
   check( perm != parent, "permission cannot be its own parent" );
   check( perm.to_string().find( "ra." ) != 0, "permission names starting with ra. are reserved" );
   if( period_sec != 0 )
      check( step != 0, "step must be non-zero when period_sec is non-zero" );

   authority auth = make_account_authority( winners, weights, threshold );
   send_updateauth( target, parent, target, perm, parent, auth );

   const uint32_t start_sec = eosio::current_time_point().sec_since_epoch();
   send_setepoch( target, parent, target, perm, period_sec, step, start_sec );
}//END setelection()

// === Threshold Adjust === //
// --- Apply integer delta to threshold without changing signers --- //
void fractal_perms::adjthreshold( const name& target,
                                  const name& perm,
                                  const name& parent,
                                  const std::vector<name>& winners,
                                  const std::vector<uint16_t>& weights,
                                  uint32_t threshold,
                                  int32_t delta ) {
   require_auth( permission_level{ target, parent } );
   check( is_account( target ), "target account does not exist" );
   check( perm != "owner"_n && perm != "active"_n, "cannot replace owner or active" );

   const int64_t candidate = static_cast<int64_t>( threshold ) + static_cast<int64_t>( delta );
   check( candidate >= 1, "Threshold cannot be less than 1" );

   authority auth = make_account_authority( winners, weights, static_cast<uint32_t>( candidate ) );
   check( candidate <= static_cast<int64_t>( total_account_weight( auth ) ),
          "Threshold exceeds total available weight" );

   send_updateauth( target, parent, target, perm, parent, auth );
}//END adjthreshold()

// === Epoch Config === //
// --- Set or clear native epoch decay on an existing permission --- //
void fractal_perms::setdecay( const name& target,
                              const name& perm,
                              const name& parent,
                              uint32_t period_sec,
                              uint16_t step,
                              uint32_t start_sec ) {
   require_auth( permission_level{ target, parent } );
   check( is_account( target ), "target account does not exist" );
   if( period_sec != 0 )
      check( step != 0, "step must be non-zero when period_sec is non-zero" );

   send_setepoch( target, parent, target, perm, period_sec, step, start_sec );
}//END setdecay()

} // namespace fractal
