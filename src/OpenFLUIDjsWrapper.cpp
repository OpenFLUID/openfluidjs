/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.

*/

/**
  @file OpenFLUIDjsWrapper.cpp
  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
 */


#include <napi.h>

#include <openfluid/utils/Binding.hpp>


// =====================================================================
// =====================================================================


class jsOutErr : public openfluid::utils::BindingAbstractOutErr
{
  public:

    void printfOut(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      vprintf(fmt,args);
      va_end(args);
    }

    void printfErr(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      vfprintf(stderr,fmt,args);
      va_end(args);
    }
};


OPENFLUID_BINDING_DEFINE(jsOutErr);


// =====================================================================
// =====================================================================


Napi::String OpenFLUIDjs_GetVersion(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  std::string VerStr = openfluid::utils::Binding::getVersion();

  return Napi::String::New(env, VerStr);
}


// =====================================================================
// =====================================================================


void DestroyBlob(Napi::Env env, openfluid::utils::Binding* Data)
{
  openfluid::utils::Binding::destroy(Data);
}


// =====================================================================
// =====================================================================


Napi::External<openfluid::utils::Binding> OpenFLUIDjs_NewBlob(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::External<openfluid::utils::Binding> Ret;

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::make();

  if (Ptr)
  {
    Ret = Napi::External<openfluid::utils::Binding>::New(env,Ptr,DestroyBlob);
  }
  else
  {
    throw Napi::Error::New(env, "unable to create new blob");
  }

  return Ret;
}


// =====================================================================
// =====================================================================


void OpenFLUIDjs_DeleteBlob(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::External<openfluid::utils::Binding> Blob = info[0].As<Napi::External<openfluid::utils::Binding>>();

  DestroyBlob(env,Blob.Data());
}


// =====================================================================
// =====================================================================


Napi::External<openfluid::utils::Binding> OpenFLUIDjs_OpenDataset(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::External<openfluid::utils::Binding> Ret;

  if (info.Length() != 1)
  {
    throw Napi::Error::New(env, "wrong arguments");
    return Ret;
  }

  std::string Path = info[0].As<Napi::String>();

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openDataset(Path.c_str());

  if (Ptr)
  {
    Ret = Napi::External<openfluid::utils::Binding>::New(env,Ptr,DestroyBlob);
  }
  else
  {
    throw Napi::Error::New(env, "unable to open dataset");
    return Ret;
  }

  return Ret;
}


// =====================================================================
// =====================================================================


Napi::External<openfluid::utils::Binding> OpenFLUIDjs_OpenProject(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::External<openfluid::utils::Binding> Ret;

  if (info.Length() != 1)
  {
    throw Napi::Error::New(env, "wrong arguments");
    return Ret;
  }

  std::string Path = info[0].As<Napi::String>();

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openProject(Path.c_str());

  if (Ptr)
  {
    Ret = Napi::External<openfluid::utils::Binding>::New(env,Ptr,DestroyBlob);
  }
  else
  {
    throw Napi::Error::New(env, "unable to open project");
    return Ret;
  }

  return Ret;
}


// =====================================================================
// =====================================================================


void OpenFLUIDjs_PrintSimulationInfo(const Napi::CallbackInfo& info)
{
  Napi::External<openfluid::utils::Binding> Blob = info[0].As<Napi::External<openfluid::utils::Binding>>();

  Blob.Data()->printSimulationInfo();
}



// =====================================================================
// =====================================================================


void OpenFLUIDjs_SetCurrentOutputDir(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1)
  {
    throw Napi::Error::New(env, "wrong arguments");
    return;
  }

  std::string Path = info[0].As<Napi::String>();
  openfluid::utils::Binding::setCurrentOutputDir(Path.c_str());
}


// =====================================================================
// =====================================================================


void OpenFLUIDjs_RunSimulation(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 2)
  {
    throw Napi::Error::New(env, "wrong arguments");
    return;
  }

  Napi::External<openfluid::utils::Binding> Blob = info[0].As<Napi::External<openfluid::utils::Binding>>();
  bool Verbose = info[1].As<Napi::Boolean>();

  if (Blob.Data()->runSimulation(Verbose) != 1)
  {
    throw Napi::Error::New(env,openfluid::utils::Binding::getLastError());
  }
}


// =====================================================================
// =====================================================================


Napi::Object Init(Napi::Env env, Napi::Object exports) {

  openfluid::utils::Binding::init();

  exports.Set(Napi::String::New(env, "getVersion"),Napi::Function::New(env,OpenFLUIDjs_GetVersion));

  exports.Set(Napi::String::New(env, "newBlob"),Napi::Function::New(env,OpenFLUIDjs_NewBlob));
  exports.Set(Napi::String::New(env, "deleteBlob"),Napi::Function::New(env,OpenFLUIDjs_DeleteBlob));

  exports.Set(Napi::String::New(env, "openDataset"),Napi::Function::New(env,OpenFLUIDjs_OpenDataset));
  exports.Set(Napi::String::New(env, "openProject"),Napi::Function::New(env,OpenFLUIDjs_OpenProject));
  exports.Set(Napi::String::New(env, "printSimulationInfo"),Napi::Function::New(env,OpenFLUIDjs_PrintSimulationInfo));
  exports.Set(Napi::String::New(env, "setCurrentOutputDir"),Napi::Function::New(env,OpenFLUIDjs_SetCurrentOutputDir));
  exports.Set(Napi::String::New(env, "runSimulation"),Napi::Function::New(env,OpenFLUIDjs_RunSimulation));

  return exports;

}


NODE_API_MODULE(OpenFLUIDjs, Init)
