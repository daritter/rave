#ifndef _RaveToCmsObjects_H_
#define _RaveToCmsObjects_H_

#include "TrackingTools/TrajectoryParametrization/interface/CartesianTrajectoryError.h"
#include "TrackingTools/TrajectoryParametrization/interface/GlobalTrajectoryParameters.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/GlobalError.h"
#include "DataFormats/GeometrySurface/interface/Plane.h"
#include "DataFormats/GeometrySurface/interface/Cylinder.h"
#include <rave/Charge.h>
#include <rave/Point3D.h>
#include <rave/Vector3D.h>
#include <rave/Vector6D.h>
#include <rave/Covariance3D.h>
#include <rave/Covariance6D.h>
#include <rave/PerigeeParameters5D.h>
#include <rave/PerigeeCovariance5D.h>

#ifdef WITH_KINEMATICS

#include <rave/Vector4D.h>
#include <rave/Vector7D.h>
#include <rave/Covariance4D.h>
#include <rave/Covariance7D.h>

#include <rave/PerigeeParameters6D.h>
#include <rave/PerigeeCovariance6D.h>

#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParameters.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParametersError.h"

#include "RecoVertex/KinematicFitPrimitives/interface/ExtendedPerigeeTrajectoryParameters.h"
#include "RecoVertex/KinematicFitPrimitives/interface/ExtendedPerigeeTrajectoryError.h"

#endif

namespace rave
{
class Track;
class Vertex;
class Coviarance6D;
class Plane;
class Cylinder;
typedef signed TrackCharge;
}

namespace ravesurf
{
class Plane;
class Cylinder;
}

class RaveToCmsObjects
{
  public:
    CartesianTrajectoryError convert ( const rave::Covariance6D & ) const;
    GlobalPoint convert ( const rave::Point3D & ) const;
    GlobalPoint convert ( const rave::Vector3D & ) const;
    GlobalVector toVector ( const rave::Vector3D & ) const;
    AlgebraicVector toAlgebraicVector ( const rave::Vector3D & ) const;
    AlgebraicVector3 toAlgebraicVector3 ( const rave::Vector3D & ) const;
    GlobalError convert ( const rave::Covariance3D & ) const;
    reco::TransientTrack tTrack ( const rave::Track & ) const;

    PerigeeTrajectoryParameters convert(const rave::PerigeeParameters5D &, const rave::Charge &) const;
    PerigeeTrajectoryError convert(const rave::PerigeeCovariance5D &) const;
    Plane convert ( const ravesurf::Plane & ) const;
    Cylinder convert ( const ravesurf::Cylinder & ) const;

    #ifdef WITH_KINEMATICS
    AlgebraicVector toAlgebraicVector(const rave::Vector4D &) const;
    ::KinematicParameters convert(const rave::Vector7D &) const;
    AlgebraicSymMatrix toAlgebraicSymMatrix(const rave::Covariance4D &) const;
    ::KinematicParametersError convert(const rave::Covariance7D &) const;

    ExtendedPerigeeTrajectoryParameters convert(
        const rave::PerigeeParameters6D &, const rave::Charge &) const;
    ExtendedPerigeeTrajectoryError convert(
        const rave::PerigeeCovariance6D &) const;
    #endif
};

#endif
