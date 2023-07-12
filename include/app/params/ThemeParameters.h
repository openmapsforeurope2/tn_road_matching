
#ifndef _APP_THEMEPARAMETERS_
#define _APP_THEMEPARAMETERS_

#include <epg/params/ParametersT.h>

//SOCLE
#include <ign/Exception.h>



	enum TRANS_PARAMETERS{

		SOURCE_ROAD_TABLE,

		EDGE_NATIONAL_ROAD_CODE,
		EDGE_EUROPEAN_ROAD_CODE,
		NATIONAL_IDENTIFIER,

		SQL_FILTER_EDGES_2_GENERATE_CF

	};

namespace app{
namespace params{

	class TransParameters : public epg::params::ParametersT< TRANS_PARAMETERS >
	{
		typedef  epg::params::ParametersT< TRANS_PARAMETERS > Base;

		public:

			/// \brief
			TransParameters()
			{				
				_initParameter( SOURCE_ROAD_TABLE, "SOURCE_ROAD_TABLE" )  ;

				_initParameter(NATIONAL_IDENTIFIER, "NATIONAL_IDENTIFIER");
				_initParameter(EDGE_NATIONAL_ROAD_CODE, "EDGE_NATIONAL_ROAD_CODE");
				_initParameter(EDGE_EUROPEAN_ROAD_CODE, "EDGE_EUROPEAN_ROAD_CODE" ) ;

				_initParameter(SQL_FILTER_EDGES_2_GENERATE_CF, "SQL_FILTER_EDGES_2_GENERATE_CF");
			}

			/// \brief
			~TransParameters()
			{
			}

			/// \brief
			virtual std::string getClassName()const
			{
				return "TransParameters";
			}

			/// \brief
			/*virtual void loadParameter( std::string const& parameterName, std::string const& parameterValue )
			{
				right_it it = _mParamName.right.find( parameterName );
				if( it == _mParamName.right.end() )
					IGN_THROW_EXCEPTION( "[epg::"+getClassName()+"] parameter "+parameterName+" does not exist" );

				setParameter( it->second, parameterValue );
			}*/
	};

	typedef epg::Singleton< TransParameters >  TransParametersS;

}
}

#endif