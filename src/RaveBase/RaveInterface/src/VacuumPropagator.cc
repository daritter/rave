#include "RaveBase/RaveInterface/rave/VacuumPropagator.h"
#include "TrackingTools/PatternTools/interface/TransverseImpactPointExtrapolator.h"
// #include "RaveTools/Converters/interface/MagneticFieldSingleton.h"
#include "TrackingTools/TrajectoryState/interface/PerigeeConversions.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include "DataFormats/GeometrySurface/interface/GloballyPositioned.h"
#include "rave/Plane.h"
#include "rave/Cylinder.h"

#include "RaveBase/Converters/interface/CmsToRaveObjects.h"
#include "RaveBase/Converters/interface/RaveToCmsObjects.h"
#include "RaveBase/Converters/interface/RaveStreamers.h"
#include <iostream>


using namespace std;

namespace {
  // FIXME really really ugly work around for reference counting probs!
  std::vector < const TrajectoryStateOnSurface * > tsoses;
  void clearTsoses()
  {
    /*
    cout << "[VacuumPropagator] clearing!" << endl;
    for ( vector< const TrajectoryStateOnSurface * >::const_iterator 
          i=tsoses.begin(); i!=tsoses.end() ; ++i )
      delete (*i);
    tsoses.clear();
    */
  }
}


shared_ptr< rave::Propagator > rave::VacuumPropagator::copy() const
{


	return make_shared < rave::VacuumPropagator > ( * this ); /* TODO actually copy object here */
}


pair < rave::Track, double > rave::VacuumPropagator::to ( const rave::Track & orig,
                          const ravesurf::Cylinder & rcyl ) const
{

  clearTsoses();
  typedef GloballyPositioned<float>::PositionType PositionType;
  typedef GloballyPositioned<float>::RotationType RotationType;
  AnalyticalPropagator prop ( orig.getMagneticFieldPtr(), anyDirection );
  pair < rave::Track, double > ot = prop.propagateWithPath ( orig, rcyl );
  return ot;
}

rave::VacuumPropagator::~VacuumPropagator()
{
  clearTsoses();
}


pair < rave::Track, double > rave::VacuumPropagator::to ( const rave::Track & orig,
                          const ravesurf::Plane & rplane ) const
{
  tsoses.clear();
  typedef GloballyPositioned<float>::PositionType PositionType;

  AnalyticalPropagator prop ( orig.getMagneticFieldPtr(), anyDirection );
  pair < rave::Track, double > to = prop.propagateWithPath ( orig, rplane );
  return to;
}


rave::Track rave::VacuumPropagator::closestTo ( const rave::Track & orig,
    const rave::Point3D & pt, bool transverse ) const
{
  /*RaveToCmsObjects forward;

  GlobalPoint pos =  forward.convert ( pt );*/
  GlobalPoint pos = pt;

  if ( transverse )
  {
    TransverseImpactPointExtrapolator tipe( orig.getMagneticFieldPtr() );
    TrajectoryStateOnSurface tsos = tipe.extrapolate( orig, pos );
    rave::Track ret ( orig.id(), tsos.globalParameters(), tsos.cartesianError(), orig.chi2(), orig.ndof(), orig.originalObject(), orig.tag() );
    return ret;
  }
  

  PerigeeConversions conv;
  AlgebraicVector3 momentum = orig.parameters().momVector();
  AlgebraicSymMatrix66 error = orig.cartesianError().matrix();
  TrajectoryStateClosestToPoint tscp = conv.trajectoryStateClosestToPoint( momentum, pos, orig.charge(), error , orig.getMagneticFieldPtr()  );
  rave::Track ret ( orig.id(), tscp.theState().parameters(), tscp.theState().cartesianError() , orig.chi2(), orig.ndof(), orig.originalObject(), orig.tag() );

  return ret;
}


rave::VacuumPropagator::VacuumPropagator() {}
