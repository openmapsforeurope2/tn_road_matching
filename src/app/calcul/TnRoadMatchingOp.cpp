#include <app/calcul/TnRoadMatchingOp.h>



//EPG
#include <epg/Context.h>
#include <epg/tools/TimeTools.h>
#include <epg/utils/replaceTableName.h>
#include <epg/utils/CopyTableUtils.h>
#include <epg/calcul/selection/SelectionFromConnectingFeatures.h>

//APP
#include <app/params/ThemeParameters.h>

void app::calcul::TnRoadMatchingOp::compute(
	std::string countryCode,
	std::string borderCode,
	bool verbose)
{
	TnRoadMatchingOp tnRoadMatchingOp(countryCode, borderCode, verbose);
	tnRoadMatchingOp._compute();
}


app::calcul::TnRoadMatchingOp::TnRoadMatchingOp(std::string countryCode,
	std::string borderCode,
	bool verbose)
{
	_init(countryCode, borderCode,verbose);
}

app::calcul::TnRoadMatchingOp::~TnRoadMatchingOp()
{
	epg::log::ShapeLoggerS::kill();
}


///
///
///
void app::calcul::TnRoadMatchingOp::_init(std::string countryCode,
	std::string borderCode,
	bool verbose)
{
	_logger = epg::log::EpgLoggerS::getInstance();
	_logger->log(epg::log::TITLE, "[ BEGIN INITIALIZATION ] : " + epg::tools::TimeTools::getTime());


	epg::Context* context = epg::ContextS::getInstance();
	params::TransParameters* themeParameters = params::TransParametersS::getInstance();
	std::string const idName = context->getEpgParameters().getValue(ID).toString();
	std::string const geomName = context->getEpgParameters().getValue(GEOM).toString();

	_shapeLogger = epg::log::ShapeLoggerS::getInstance();


	_countryCode = countryCode;
	_borderCode = borderCode;
	_verbose = verbose;

	std::string edgeSourceTableName = themeParameters->getValue(SOURCE_ROAD_TABLE).toString();
	std::string edgeTargetTableName = "_110_" + epg::utils::replaceTableName(themeParameters->getValue(SOURCE_ROAD_TABLE).toString());
	context->getEpgParameters().setParameter(EDGE_TABLE, ign::data::String(edgeTargetTableName));

	epg::utils::CopyTableUtils::copyEdgeTable(edgeSourceTableName, "", false);

	_fsEdge = context->getFeatureStore(epg::EDGE);

	std::string const boundaryTableName = epg::utils::replaceTableName(context->getEpgParameters().getValue(TARGET_BOUNDARY_TABLE).toString());
	_fsBoundary = context->getDataBaseManager().getFeatureStore(boundaryTableName, idName, geomName);
	std::string cpTableName = epg::utils::replaceTableName(context->getEpgParameters().getValue(CONNECT_POINT_TABLE).toString());
	_fsTmpCP = context->getDataBaseManager().getFeatureStore(cpTableName, idName, geomName);
	std::string clTableName = epg::utils::replaceTableName(context->getEpgParameters().getValue(CONNECT_LINE_TABLE).toString());
	_fsTmpCL = context->getDataBaseManager().getFeatureStore(clTableName, idName, geomName);


	_logger->log(epg::log::TITLE, "[ END INITIALIZATION ] : " + epg::tools::TimeTools::getTime());
}

void app::calcul::TnRoadMatchingOp::_compute()
{


}