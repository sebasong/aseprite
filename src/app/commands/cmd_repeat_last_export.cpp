// Aseprite
// Copyright (C) 2001-2016  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/app.h"
#include "app/commands/command.h"
#include "app/commands/commands.h"
#include "app/commands/params.h"
#include "app/context.h"
#include "app/context_access.h"
#include "app/pref/preferences.h"

namespace app {

class RepeatLastExportCommand : public Command {
public:
  RepeatLastExportCommand();
  Command* clone() const override { return new RepeatLastExportCommand(*this); }

protected:
  virtual bool onEnabled(Context* context) override;
  virtual void onExecute(Context* context) override;
};

RepeatLastExportCommand::RepeatLastExportCommand()
  : Command("RepeatLastExport",
            "Repeat Last Export",
            CmdRecordableFlag)
{
}

bool RepeatLastExportCommand::onEnabled(Context* context)
{
  return context->checkFlags(ContextFlags::ActiveDocumentIsWritable);
}

void RepeatLastExportCommand::onExecute(Context* context)
{
  Command* cmd = CommandsModule::instance()->getCommandByName(CommandId::ExportSpriteSheet);
  Params params;

  {
    const ContextReader reader(context);
    const Document* document(reader.document());
    DocumentPreferences& docPref =
      Preferences::instance().document(document);

    params.set("ui", (docPref.spriteSheet.defined() ? "0": "1"));
  }

  context->executeCommand(cmd, params);
}

Command* CommandFactory::createRepeatLastExportCommand()
{
  return new RepeatLastExportCommand;
}

} // namespace app
