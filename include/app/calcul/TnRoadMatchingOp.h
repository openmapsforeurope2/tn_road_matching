#ifndef _APP_CALCUL_TNROADMATCHINGOP_H_
#define _APP_CALCUL_TNROADMATCHINGOP_H_



#include <epg/log/EpgLogger.h>
#include <epg/log/ShapeLogger.h>
#include <epg/sql/tools/IdGeneratorFactory.h>

namespace app{
namespace calcul{

	class TnRoadMatchingOp {

	public:

		static void compute(std::string countryCode, bool verbose);


	private:


		TnRoadMatchingOp(std::string countryCode, bool verbose);
		~TnRoadMatchingOp();

		void _init(std::string countryCode, bool verbose);
		void _compute();
		//void _computeOnDoubleCC(std::string countryCodeDouble);


		
	private:
		ign::feature::sql::FeatureStorePostgis* _fsEdge;
		ign::feature::sql::FeatureStorePostgis* _fsBoundary;
		ign::feature::sql::FeatureStorePostgis* _fsTmpCP;
		ign::feature::sql::FeatureStorePostgis* _fsTmpCL;

		//ign::feature::FeatureFilter _filterEdges2generateCF;
		std::string _reqFilterEdges2generateCF;

		epg::log::EpgLogger*                               _logger;
		//--
		epg::log::ShapeLogger*                             _shapeLogger;
		//--
		std::string                                        _countryCode;
		//--
		bool                                               _verbose;

	};

}
}

#endif