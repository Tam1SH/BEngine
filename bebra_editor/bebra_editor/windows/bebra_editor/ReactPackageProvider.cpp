#include "pch.h"
#include "ReactPackageProvider.h"
#include "NativeModules.h"
#include <ModuleRegistration.h>
#include "Jopa.hpp"
using namespace winrt::Microsoft::ReactNative;

namespace winrt::bebra_editor::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
    AddAttributedModules(packageBuilder);
}

} // namespace winrt::bebra_editor::implementation
