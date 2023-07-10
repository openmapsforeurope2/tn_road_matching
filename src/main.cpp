//BOOST
#include <boost/program_options.hpp>

//SOCLE
#include <ign/Exception.h>

//EPG
#include <epg/Context.h>
#include <app/params/ThemeParameters.h>
#include <epg/log/EpgLogger.h>
#include <epg/tools/TimeTools.h>
#include <epg/SingletonT.h>
#include <epg/params/tools/loadParameters.h>

#include <app/calcul/TnRoadMatchingOp.h>

namespace po = boost::program_options;

int main(int argc, char *argv[])
{

	epg::Context* context=epg::ContextS::getInstance();

	std::string     logDirectory = "";
	std::string     epgParametersFile = "";
	std::string     transParametersFile = "";
	std::string     countryCode = "";
	bool            verbose = true;


	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("c", po::value< std::string >(&epgParametersFile), "conf file")
		("cc", po::value< std::string >(&countryCode), "country code")
		//("th", po::value< std::string >(&countryCode), "theme")
		;


	//main log
	std::string     logFileName = "log.txt";
	std::ofstream   logFile(logFileName.c_str());

	logFile << "[START] " << epg::tools::TimeTools::getTime() << std::endl;

	ign::geometry::PrecisionModel::SetDefaultPrecisionModel(ign::geometry::PrecisionModel(ign::geometry::PrecisionModel::FIXED, 1.0e5, 1.0e7));

	int returnValue = 0;
	try {

		po::variables_map vm;
		int style = po::command_line_style::default_style & ~po::command_line_style::allow_guessing;
		po::store(po::parse_command_line(argc, argv, desc, style), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}

		//parametres EPG
		context->loadEpgParameters(epgParametersFile);

		//Initialisation du log de prod
		logDirectory = context->getConfigParameters().getValue(LOG_DIRECTORY).toString();

		//test si le dossier de log existe sinon le creer
		boost::filesystem::path logDir(logDirectory);
		if (!boost::filesystem::is_directory(logDir))
		{
			if (!boost::filesystem::create_directory(logDir))
			{
				std::string mError = "le dossier " + logDirectory + " ne peut �tre cree";
				IGN_THROW_EXCEPTION(mError);
			}
		}

		epg::log::EpgLogger* logger = epg::log::EpgLoggerS::getInstance();
		logger->setDevOfstream(logDirectory + "/connectFeatGeneration.log");

		//repertoire de travail
		context->setLogDirectory(logDirectory);

		//theme parameters
		transParametersFile = context->getConfigParameters().getValue(THEME_PARAMETER_FILE).toString();
		app::params::TransParameters* transParameters = app::params::TransParametersS::getInstance();
		epg::params::tools::loadParams(*transParameters, transParametersFile);

		//lancement du traitement
		app::calcul::TnRoadMatchingOp::compute(countryCode, verbose);

	}
	catch (ign::Exception &e)
	{
		std::cerr << e.diagnostic() << std::endl;
		epg::log::EpgLoggerS::getInstance()->log(epg::log::ERROR, std::string(e.diagnostic()));
		logFile << e.diagnostic() << std::endl;
		returnValue = 1;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		epg::log::EpgLoggerS::getInstance()->log(epg::log::ERROR, std::string(e.what()));
		logFile << e.what() << std::endl;
		returnValue = 1;
	}

	logFile << "[END] " << epg::tools::TimeTools::getTime() << std::endl;

	epg::ContextS::kill();
	epg::log::EpgLoggerS::kill();;
	app::params::TransParametersS::kill();;

	logFile.close();

	return returnValue;



}

