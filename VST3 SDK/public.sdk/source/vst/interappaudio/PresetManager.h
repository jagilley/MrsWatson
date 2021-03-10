//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.6
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/interappaudio/PresetManager.h
// Created by  : Steinberg, 10/2013
// Description : VST 3 InterAppAudio
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2016, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// This Software Development Kit may not be distributed in parts or its entirety
// without prior written agreement by Steinberg Media Technologies GmbH.
// This SDK must not be used to re-engineer or manipulate any technology used
// in any Steinberg or Third-party application or software module,
// unless permitted by law.
// Neither the name of the Steinberg Media Technologies nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SDK IS PROVIDED BY STEINBERG MEDIA TECHNOLOGIES GMBH "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL STEINBERG MEDIA TECHNOLOGIES GMBH BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#pragma once

#include "VST3Plugin.h"
#include "pluginterfaces/vst/ivstinterappaudio.h"
#include "base/source/fstring.h"

#if __OBJC__
@class NSArray, PresetBrowserViewController, PresetSaveViewController;
#else
struct NSArray;
struct PresetBrowserViewController;
struct PresetSaveViewController;
#endif

namespace Steinberg {
namespace Vst {
namespace InterAppAudio {

class PresetManager : public FObject, public IInterAppAudioPresetManager
{
public:
	PresetManager (VST3Plugin* plugin, const TUID& cid);

	tresult PLUGIN_API runLoadPresetBrowser () override;
	tresult PLUGIN_API runSavePresetBrowser () override;
	tresult PLUGIN_API loadNextPreset () override;
	tresult PLUGIN_API loadPreviousPreset () override;

	DEFINE_INTERFACES
		DEF_INTERFACE(IInterAppAudioPresetManager)
	END_DEFINE_INTERFACES(FObject)
	REFCOUNT_METHODS(FObject)

private:
	enum PresetPathType {
		kFactory,
		kUser
	};
	NSArray* getPresetPaths (PresetPathType type);

	tresult loadPreset (bool next);
	tresult loadPreset (const char* path);
	void savePreset (const char* path);

	VST3Plugin* plugin;
	PresetBrowserViewController* visiblePresetBrowserViewController;
	PresetSaveViewController* visibleSavePresetViewController;
	FUID cid;
	String lastPreset;
};

//------------------------------------------------------------------------
} // namespace InterAppAudio
} // namespace Vst
} // namespace Steinberg

