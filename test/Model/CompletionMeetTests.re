open EditorCoreTypes;
open TestFramework;

module CompletionMeet = Oni_Model.CompletionMeet;

describe("CompletionMeet", ({describe, _}) => {
  describe("createFromLine", ({test, _}) => {
    let line0column0 = Location.{line: Index.zero, column: Index.zero};
    let line0column1 = Location.{line: Index.zero, column: Index.(zero + 1)};
    let line0column2 = Location.{line: Index.zero, column: Index.(zero + 2)};
    let line0column8 = Location.{line: Index.zero, column: Index.(zero + 8)};

    test("empty line - no meet", ({expect}) => {
      let result = CompletionMeet.createFromLine(~index=Index.zero, "");
      expect.equal(result, None);
    });

    test("single character at beginning", ({expect}) => {
      let result =
        CompletionMeet.createFromLine(~index=Index.(zero + 1), "a");

      let expected = CompletionMeet.create(~location=line0column0, ~base="a");

      expect.equal(result, Some(expected));
    });

    test("spaces prior to character", ({expect}) => {
      let result =
        CompletionMeet.createFromLine(~index=Index.(zero + 1), " a");

      let expected = CompletionMeet.create(~location=line0column1, ~base="a");
      expect.equal(result, Some(expected));
    });

    test("longer base", ({expect}) => {
      let result =
        CompletionMeet.createFromLine(~index=Index.(zero + 4), " abc");
      let expected =
        CompletionMeet.create(~location=line0column1, ~base="abc");
      expect.equal(result, Some(expected));
    });

    test("default trigger character", ({expect}) => {
      let result =
        CompletionMeet.createFromLine(~index=Index.(zero + 1), " .");
      let expected = CompletionMeet.create(~location=line0column2, ~base="");
      expect.equal(result, Some(expected));
    });

    test("default trigger character with base", ({expect}) => {
      let result =
        CompletionMeet.createFromLine(~index=Index.(zero + 10), "console.lo");
      let expected =
        CompletionMeet.create(~location=line0column8, ~base="lo");
      expect.equal(result, Some(expected));
    });
  })
});
