#include "GSMS.h"
#include <geant/Randomize.hh>

#include <geant/G4VisExecutive.hh>
#include <geant/G4UImanager.hh>
#include <geant/G4UIterminal.hh>
#include <geant/G4UItcsh.hh>

#include "action/RunAction.h"
#include "action/EventAction.h"

GSMS::GlobalConfig	GSMS::GSMS::m_global;
GSMS::MaskConfig	GSMS::GSMS::m_mask;
GSMS::HullConfig	GSMS::GSMS::m_hull;
GSMS::Job		GSMS::GSMS::m_job;
GSMS::DetectorConfig	GSMS::GSMS::m_detector;
GSMS::SceneConfig	GSMS::GSMS::m_scene;

GSMS::PhysicsList*	GSMS::GSMS::mp_physics = NULL;
GSMS::Geometry*		GSMS::GSMS::mp_geometry = NULL;
GSMS::Generator*	GSMS::GSMS::mp_generator = NULL;

G4RunManager*		GSMS::GSMS::mp_runmanager = NULL;

G4int			GSMS::GSMS::m_verbosity = 0;

unsigned int	GSMS::GSMS::getMaterial(std::string name,G4Material** material)
{
	if(mp_geometry)
		return mp_geometry->getMaterial(name,material);
	else
		return GSMS_ERR;
}

unsigned int	GSMS::GSMS::initRunManager()
{
//	try
//	{
		CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
		CLHEP::HepRandom::setTheSeed(0L);

		mp_runmanager = new G4RunManager;
		mp_runmanager->SetVerboseLevel(0);//m_verbosity);
		
		mp_physics = new PhysicsList;
		mp_runmanager->SetUserInitialization(mp_physics);

		mp_geometry = new Geometry;
		mp_runmanager->SetUserInitialization(mp_geometry);

		mp_generator = new Generator;
		mp_runmanager->SetUserAction(mp_generator);

		G4UserRunAction*	run_action = new RunAction;
		mp_runmanager->SetUserAction(run_action);

		G4UserEventAction*	event_action = new EventAction;
		mp_runmanager->SetUserAction(event_action);

		mp_runmanager->Initialize();

//		G4UImanager*	ui = G4UImanager::GetUIpointer();
//		G4VisManager*	vis = new G4VisExecutive;
//		vis->Initialize();
//		ui->ApplyCommand("/control/execute vis.mac");
//		ui->ApplyCommand("/tracking/verbose 1");

//		G4UIsession*	session = NULL;
//		session = new G4UIterminal();
//		session->SessionStart();
//		delete session;

		Source*	src = util::SourceLib::create_source("Cs137", 1, G4ThreeVector(1.*m, 1.*m, 0.));
		if(src) m_job.push_source(*src);

//		src = util::SourceLib::create_source("Co57", 1, G4ThreeVector(1.*m, 0., 0.));
//		if(src) m_job.push_source(*src);

//		src = util::SourceLib::create_source("Co60", 1, G4ThreeVector(0., -1.*m, 0.));
//		if(src) m_job.push_source(*src);		

		serialize("text.gz");

		int	discretes = 217;

		for(int i = 0; i<discretes ; i++) {

		G4double	ltime = ((G4double)i / discretes)*10*2*pi;
		setTime(&ltime);
		if(i)
			mp_geometry->Update();
			mp_generator->Update();
//		if(	__SUCCEEDED(setTime(&ltime)) &&
//			__SUCCEEDED(imprintMask()))
				mp_runmanager->BeamOn(12000);
	}
//	catch(...)
//	{
//		return GSMS_ERR;
//	};
	return GSMS_OK;
}

unsigned int	GSMS::GSMS::serialize(std::string filename)
{
	try
	{
		std::stringstream	sout;
		boost::archive::xml_oarchive oa(sout);
		oa	<< BOOST_SERIALIZATION_NVP(m_mask)
			<< BOOST_SERIALIZATION_NVP(m_global)
			<< BOOST_SERIALIZATION_NVP(m_hull)
			<< BOOST_SERIALIZATION_NVP(m_detector)
			<< BOOST_SERIALIZATION_NVP(m_job);
//			<< BOOST_SERIALIZATION_NVP(m_scene);
		std::ofstream file_out(filename.c_str(),std::ios::out | std::ios::binary);

		boost::iostreams::filtering_ostreambuf out;
		out.push(boost::iostreams::gzip_compressor());
		out.push(file_out);
		copy(sout,out);
	}
	catch(...)
	{
		return GSMS_ERR;
	};

	return GSMS_OK;
};

unsigned int	GSMS::GSMS::unserialize(std::string filename)
{
	try
	{
		std::ifstream file_in(filename.c_str(),std::ios::in | std::ios::binary);
		std::stringstream	sin;

		boost::iostreams::filtering_istreambuf in;
		in.push(boost::iostreams::gzip_decompressor());
		in.push(file_in);
		copy(in,sin);

		boost::archive::xml_iarchive ia(sin);
		ia	>> BOOST_SERIALIZATION_NVP(m_mask)
			>> BOOST_SERIALIZATION_NVP(m_global)
			>> BOOST_SERIALIZATION_NVP(m_hull)
			>> BOOST_SERIALIZATION_NVP(m_detector)
			>> BOOST_SERIALIZATION_NVP(m_job)
			>> BOOST_SERIALIZATION_NVP(m_scene);
	}
	catch(...)
	{
		return GSMS_ERR;
	};

	return GSMS_OK;
};
