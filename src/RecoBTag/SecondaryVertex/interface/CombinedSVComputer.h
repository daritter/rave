#ifndef RecoBTag_SecondaryVertex_CombinedSVComputer_h
#define RecoBTag_SecondaryVertex_CombinedSVComputer_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"  
#include "DataFormats/BTauReco/interface/TaggingVariable.h"

#include "RecoBTag/SecondaryVertex/interface/TrackSelector.h"
#include "RecoBTag/SecondaryVertex/interface/V0Filter.h"

class CombinedSVComputer {
    public:
	CombinedSVComputer(const edm::ParameterSet &params);

	reco::TaggingVariableList
	operator () (const reco::TrackIPTagInfo &ipInfo,
	             const reco::SecondaryVertexTagInfo &svInfo) const;

    private:
	const reco::TrackIPTagInfo::TrackIPData &
	threshTrack(const reco::TrackIPTagInfo &trackIPTagInfo,
	            const reco::TrackIPTagInfo::SortCriteria sort) const;

	double					charmCut;
	reco::TrackIPTagInfo::SortCriteria	sortCriterium;
	reco::TrackSelector			trackSelector;
	reco::TrackSelector			trackPseudoSelector;
	unsigned int				pseudoMultiplicityMin;
	unsigned int				trackMultiplicityMin;
	double					minTrackWeight;
	bool					useTrackWeights;
	bool					vertexMassCorrection;
	reco::V0Filter				pseudoVertexV0Filter;
	reco::V0Filter				trackPairV0Filter;
};

#endif // RecoBTag_SecondaryVertex_CombinedSVComputer_h
