module App = {
  [@react.component]
  let make = (~children) => {
    <div>
      children
    </div>;
  };
  // [@react.component]
  // let make = () =>
  //   <div>
  //     <h1> {React.string("melange-opam-template")} </h1>
  //     {["Hello " ++ World.name ++ "!", "This is ReasonReact!"]
  //      |> List.map(text =>
  //           <div key=text style>
  //             {React.string(text)}
  //             <button
  //               onClick={_ => text |> Speech.makeUtterance |> Speech.speak}>
  //               {React.string("speak")}
  //             </button>
  //           </div>
  //         )
  //      |> Array.of_list
  //      |> React.array}
  //   </div>;
};

let () =
  switch (ReactDOM.querySelector("#root")) {
  | None =>
    Js.Console.error("Failed to start React: couldn't find the #root element")
  | Some(element) =>
    let root = ReactDOM.Client.createRoot(element);
    ReactDOM.Client.render(root,
      <App>
        <Sheet.Sheet nMeasures={4} /> 
      </App>);
  };
