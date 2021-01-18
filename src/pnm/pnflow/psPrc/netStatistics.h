#ifndef NETSTATISTICS_H
#define NETSTATISTICS_H
/*---------------------------------------------------------------------------*\
Developed by (2015): Ali Q Raeini  email: a.q.raeini@imperial.ac.uk
\*---------------------------------------------------------------------------*/


#include <vector>
#include "../Element.h"






void printCornerAngStatistics(   const std::vector<Element const *>&  rockLattices, int nBSs_, int nBpPors_);
void printCornerNumStatistics(   const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);
void printShapeFactorStatistics( const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);
void printRadiusStatistics(      const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);
void printAspectRatioStatistics( const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);
void printCoordinaNumStatistics( const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);
void printDistanceMapStatistics( const std::vector<Element const *>&  rockLattices, int nBSs_, int nPores_);




//void writeOilGangliaDistribution(string fileName, const std::vector< std::vector<Element*> >	& trappedRegionsOil );
//void writeWatGangliaDistribution( const std::vector< std::vector< std::pair<Element*,FluidBlob> > > & trappedRegionsWat );


#endif

