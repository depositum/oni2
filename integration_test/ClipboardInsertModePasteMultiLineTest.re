open Oni_Core;
open Oni_Model;
open Oni_IntegrationTestLib;

runTest(
  ~name="InsertMode test - effects batched to runEffects",
  (dispatch, wait, runEffects) => {
  wait(~name="Initial mode is normal", (state: State.t) =>
    state.mode == Vim.Types.Normal
  );

  dispatch(KeyboardInput("i"));

  wait(~name="Mode switches to insert", (state: State.t) =>
    state.mode == Vim.Types.Insert
  );

  setClipboard(Some("def\nghi"));

  dispatch(KeyboardInput("A"));
  dispatch(Command("editor.action.clipboardPasteAction"));
  dispatch(KeyboardInput("B"));

  runEffects();

  wait(~name="Buffer is correct", (state: State.t) =>
    switch (Selectors.getActiveBuffer(state)) {
    | None => false
    | Some(buf) =>
      let line1 = Buffer.getLine(buf, 0);
      let line2 = Buffer.getLine(buf, 1);
      Log.info("Line1 is: " ++ line1 ++ "|");
      Log.info("Line2 is: " ++ line2 ++ "|");
      String.equal(line1, "Adef") && String.equal(line2, "ghiB");
    }
  );
});
