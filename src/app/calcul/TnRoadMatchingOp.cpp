#include <app/calcul/TnRoadMatchingOp.h>



//EPG
#include <epg/Context.h>
#include <epg/tools/TimeTools.h>

//APP
#include <app/params/ThemeParameters.h>

void app::calcul::TnRoadMatchingOp::compute(
	std::string countryCode,
	bool verbose)
{
	TnRoadMatchingOp tnRoadMatchingOp(countryCode, verbose);
	tnRoadMatchingOp._compute();
}


app::calcul::TnRoadMatchingOp::TnRoadMatchingOp(std::string countryCode,
	bool verbose)
{
	_init(countryCode, verbose);
}

app::calcul::TnRoadMatchingOp::~TnRoadMatchingOp()
{
	epg::log::ShapeLoggerS::kill();
}


///
///
///
void app::calcul::TnRoadMatchingOp::_init(std::string countryCode, bool verbose)
{
	_logger = epg::log::EpgLoggerS::getInstance();
	_logger->log(epg::log::TITLE, "[ BEGIN INITIALIZATION ] : " + epg::tools::TimeTools::getTime());


	epg::Context* context = epg::ContextS::getInstance();
	params::TransParameters* themeParameters = params::TransParametersS::getInstance();


	_shapeLogger = epg::log::ShapeLoggerS::getInstance();



	_logger->log(epg::log::TITLE, "[ END INITIALIZATION ] : " + epg::tools::TimeTools::getTime());
}

void app::calcul::TnRoadMatchingOp::_compute()
{


}