//
// main() function for the factory simulation
//
// The code you write for hw4 must use this main()
// to run the program.
//
// usage: ./a.out number-of-assembly-lines rate1 [rate2 ...] < list_of_packages
//
// Each rate is given as number of units per time unit ("minute").
// The rates can contain fractional parts.
//
// history:
//      2013-10-31      modified for multi-line version
//      2013-10-11      original version of this file
//

#include <cstdlib>              // for atof()
#include "factory.h"
using namespace std;

int main(int ac, char *av[])
{
  double  *rates;
  int     num_workers;
  int     result;
  int     i;

  if ( ac < 3 ){
    cerr << "usage: " << av[0] << ": num_workers rate1 [rate2 ...]\n";
    exit(1);
  }

  num_workers = atoi(av[1]);      // get number of workers
  if ( ac-2 != num_workers ){     // deduct 1 for cmd, 1 for count
      cerr << av[0] << ": incorrect number of rates\n";
      exit(1);
  }

  rates = new double[num_workers];
  for(i=2; i<ac; i++)
    rates[i-2] = atof(av[i]);

  Factory fac(num_workers, rates);
  result = fac.run();
  return result;
}
