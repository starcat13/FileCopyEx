#include "FarMacro.h"

#include "Framework/StringVector.h"
#include "common.h"
#include "guid.hpp"

String base;

String getEnv(const String& name)
{
	wchar_t *buf;
	size_t len;
	if (_wdupenv_s(&buf, &len, name.c_str()) == 0) {
		String v(buf);
		free(buf);
		return v;
	}
	return "";
}

void Bind(const String& key, const String& code, const String& desc)
{
	/*
	MacroAddMacro macro = { sizeof(MacroAddMacro) };
	macro.Id = id;
	macro.SequenceText = seq.c_str();
	macro.Description = desc.c_str(); // !!! put something
	macro.Flags = KMFLAGS_DISABLEOUTPUT;
	INPUT_RECORD ir;
	int resKey = FSF.FarNameToInputRecord(key.c_str(), &ir);
	macro.AKey = ir;
	//ShowMessage("Bind - key convert", String(resKey), FMSG_MB_OK);
	macro.Area = MACROAREA_SHELL;
	macro.Callback = NULL;
	int res = Info.MacroControl(&MainGuid, MCTL_ADDMACRO, 0, &macro);
	ShowMessage("Bind", key + L": " + String(res), FMSG_MB_OK);
	*/

	if (base.empty()) {
		base = getEnv("FARPROFILE");
	}
	if (base.empty()) {
		base = getEnv("APPDATA");
		if (!base.empty()) {
			base += "\\Far Manager\\Profile";
		}
	}
	if (base.empty()) {
		return; // Cannot find correct path
	}
	String fname = String(L"Shell_") + key + ".lua";
	StringVector v;
	v.AddString("area=\"Shell\"");
	v.AddString(String("key=\"") + key + "\"");
	v.AddString("flags=\"NoPluginPanels NoPluginPPanels NoSendKeysToPlugins\"");
	v.AddString(String("description=\"") + desc + "\"");
	v.AddString(String("code=\"") + code + "\"");
	v.saveToFile(base + "\\Macros\\internal\\" + fname);

	Info.MacroControl(&MainGuid, MCTL_LOADALL, 0, NULL);
}

/*
int Binded(const String& key)
{
	//XXX String seq = registry.GetString(regkey + "\\" + key, "Sequence", "");
	//XXX return (!seq.nicmp(menu_plug, menu_plug.len()) || !seq.icmp("F5") || !seq.icmp("F6"));
	return true;
}
*/

/*
void FarPlugin::Unbind(void *id)
{
	Info.MacroControl(&MainGuid, MCTL_DELMACRO, 0, id);
}
*/

// XXX I don't know how to replace FARMACROCOMMAND
/*
void FarPlugin::MacroCommand(const FARMACROCOMMAND& cmd)
{
	ActlKeyMacro prm;
	memset(&prm, 0, sizeof(prm));
	prm.Command = cmd;
	Info.AdvControl(Info.ModuleNumber, ACTL_KEYMACRO, &prm);
}
*/