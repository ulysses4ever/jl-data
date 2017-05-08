

cxx"""
using namespace Ubitrack;

// Global BasicFacade Methods
unsigned long long int BF_now() { return Ubitrack::Facade::BasicFacade::now(); }

// BasicFacade Member Functions
bool BF_loadDataflow( Facade::BasicFacade& facade, const char* sDfSrg ) { return facade.loadDataflow(sDfSrg); }
bool BF_loadDataflowString( Facade::BasicFacade& facade, const char* sDataflow) { return facade.loadDataflowString(sDataflow); }
void BF_clearDataflow(Facade::BasicFacade& facade) { facade.clearDataflow(); }
void BF_startDataflow(Facade::BasicFacade& facade) { facade.startDataflow(); }
void BF_stopDataflow(Facade::BasicFacade& facade) { facade.stopDataflow(); }
void BF_connectToServer(Facade::BasicFacade& facade, const char* sAddress) { facade.connectToServer(sAddress); }
void BF_sendUtqlToServer(Facade::BasicFacade& facade, const char* sUtqlFile) { facade.sendUtqlToServer(sUtqlFile); }
void BF_sendUtqlToServerString(Facade::BasicFacade& facade, const char*  buffer) { facade.sendUtqlToServerString(buffer); }

Facade::BasicMeasurement::DataType BM_getdatatype(Facade::BasicMeasurement& m) { return m.getDataType(); }
int BM_getdimx(Facade::BasicMeasurement& m) { return m.getDimX(); }
int BM_getdimy(Facade::BasicMeasurement& m) { return m.getDimY(); }
int BM_getdimz(Facade::BasicMeasurement& m) { return m.getDimZ(); }

int BSIM_getvalue(Facade::BasicScalarIntMeasurement& m) { int result; m.get(result); return result;}
"""
