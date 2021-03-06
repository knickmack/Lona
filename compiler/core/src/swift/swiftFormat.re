[@bs.module] external camelCase : string => string = "lodash.camelcase";

[@bs.module] external upperFirst : string => string = "lodash.upperfirst";

let layerName = layerName => camelCase(layerName) ++ "View";

let variableNameFromIdentifier = (rootLayerName, path) =>
  switch path {
  | [head, ...tail] =>
    switch head {
    | "parameters" => List.hd(tail)
    | "layers" =>
      switch tail {
      | [second, ...tail] when second == rootLayerName =>
        List.tl(tail)
        |> List.fold_left((a, b) => a ++ upperFirst(b), List.hd(tail))
      | [second, ...tail] =>
        tail |> List.fold_left((a, b) => a ++ upperFirst(b), layerName(second))
      | _ => "BadIdentifierName"
      }
    | _ => head
    }
  | _ => "BadIdentifierName"
  };
