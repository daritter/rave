#include "RaveBase/RaveInterface/rave/Track.h"
#include "RaveBase/RaveEngine/interface/RaveId.h"


using namespace rave;
using namespace std;


Track::Track( int id, const GlobalTrajectoryParameters & gtp, const CartesianTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag):
				FreeTrajectoryState(gtp, cte),
				theRaveCharge(gtp.charge()),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true),
				theId(id)
{theTrackId=id;}


Track::Track( const GlobalTrajectoryParameters & gtp, const CartesianTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag):
				FreeTrajectoryState(gtp, cte),
				theRaveCharge(gtp.charge()),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true),
				theId(RaveId::uniqueId())
{theId=-2;}


Track::Track( int id, const GlobalTrajectoryParameters & gtp, const CurvilinearTrajectoryError & cte,
		      float chi2, float ndof, void * originaltrack, std::string tag ):
				FreeTrajectoryState(gtp, cte),
				theRaveCharge(gtp.charge()),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(originaltrack),
				theTag(tag),
				theIsValid(true),
				theId(id)
{theTrackId=id;}


Track::Track( int id, const GlobalTrajectoryParameters & gtp,
		      float chi2, float ndof, int originaltrack,  std::string tag ):
				FreeTrajectoryState(gtp),
				theRaveCharge(gtp.charge()),
				theChi2(chi2),
				theNdof(ndof),
				thePointer(&originaltrack), // passt das? Nein
				theTag(tag),
				theIsValid(true),
				theId(id)
{theTrackId=id;}


Track::Track():
				FreeTrajectoryState(),
				theChi2(-1),
				theNdof(-1),
				thePointer(0),
				theIsValid(false),
				theId(RaveId::uniqueId())
{}


string Track::tag() const
{
  return theTag;
}


Charge Track::raveCharge() const
{
  return theRaveCharge;
}


int Track::id() const
{
  return theId;
}


void * Track::originalObject() const
{
	return thePointer;
}


const ::GlobalTrajectoryParameters & Track::state() const
{
	return theGlobalParameters;
}


const CartesianTrajectoryError & Track::CartesianError() const
{
    return theCartesianError;
}


const CurvilinearTrajectoryError & Track::CurvilinearError() const
{
    return theCurvilinearError;
}


bool Track::isValid() const
{
  return theIsValid;
}


bool Track::operator< ( const Track & o ) const
{
    return ( id() < o.id() );
}


bool Track::operator== ( const Track & o ) const
{
  return ( id() == o.id() );
}


float Track::chi2() const
{
  return theChi2;
}


float Track::ndof() const
{
  return theNdof;
}
