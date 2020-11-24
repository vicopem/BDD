#include "BDD.hpp"
#include "truth_table.hpp"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool check( Truth_Table const& tt, string const& ans )
{
  cout << "  checking function correctness";
  if ( tt == Truth_Table( ans ) )
  {
    cout << "...passed." << endl;
    return true;
  }
  else
  {
    cout << "...failed. (expect " << ans << ", but get " << tt << ")" << endl;
    return false;
  }
}

bool check( uint64_t actual, uint64_t expected )
{
  if ( actual <= expected )
  {
    cout << "...passed." << endl;
    return true;
  }
  else
  {
    cout << "...failed. (expect " << expected << ", but get " << actual << ")" << endl;
    return false;
  }
}

int main()
{
  bool passed = true;
  {
    cout << "test 00: large truth table";
    Truth_Table tt( "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );

    if ( tt.n_var() == 7 )
    {
      cout << "...passed." << endl;
    }
    else
    {
      cout << "...failed." << endl;
      passed = false;
    }
  }

  {
    cout << "test 01: computed table" << endl;
    BDD bdd( 2 );
    auto const x0 = bdd.literal( 0 );
    auto const x1 = bdd.literal( 1 );
    auto const f = bdd.XOR( bdd.AND( x0, x1 ), bdd.AND( x0, x1 ) );
    auto const tt = bdd.get_tt( f );

    passed &= check( tt, "0000" );
    cout << "  checking number of computation";
    passed &= check( bdd.num_invoke(), 4 );
  }

  {
    cout << "test 02: complemented edges" << endl;
    BDD bdd( 2 );
    auto const x0 = bdd.literal( 0 );
    auto const x1 = bdd.literal( 1 );
    auto const f = bdd.XOR( x0, x1 );
    auto const tt = bdd.get_tt( f );

    passed &= check( tt, "0110" );
    cout << "  checking BDD size (reachable nodes)";
    passed &= check( bdd.num_nodes( f ), 2 );
  }

  {
    cout << "test 03: reference count" << endl;
    BDD bdd( 2 );
    auto const x0 = bdd.literal( 0 );
    auto const x1 = bdd.literal( 1 );
    auto const f = bdd.XOR( x0, x1 );
    auto const tt = bdd.get_tt( f );

    passed &= check( tt, "0110" );
    cout << "  checking BDD size (living nodes)";
    passed &= check( bdd.num_nodes(), 2 );
  }

  return passed ? 0 : 1;
}
