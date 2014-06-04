!CHAPTER Registering and Unregistering User Functions

AQL user functions can be registered using the `aqlfunctions` object as
follows:

    var aqlfunctions = require("org/arangodb/aql/functions");

To register a function, the fully qualified function name plus the
function code must be specified.

`aqlfunctions.register(name, code, isDeterministic)`

Registers an AQL user function, identified by a fully qualified function name. The function code in code must be specified as a Javascript function or a string representation of a Javascript function.

If a function identified by name already exists, the previous function definition will be updated.

The isDeterministic attribute can be used to specify whether the function results are fully deterministic (i.e. depend solely on the input and are the same for repeated calls with the same input values). It is not used at the moment but may be used for optimisations later.

!SUBSUBSECTION Examples

  arangosh> require("org/arangodb/aql/functions").register("myfunctions::temperature::celsiustofahrenheit",
  function (celsius) {
    return celsius * 1.8 + 32;
  });

It is possible to unregister a single user function, or a whole group of user functions (identified by their namespace) in one go:

`aqlfunctions.unregister(name)`

Unregisters an existing AQL user function, identified by the fully qualified function name.

Trying to unregister a function that does not exist will result in an exception.

!SUBSUBSECTION Examples

  arangosh> require("org/arangodb/aql/functions").unregister("myfunctions::temperature::celsiustofahrenheit");
  aqlfunctions.unregisterGroup(prefix)

Unregisters a group of AQL user function, identified by a common function group prefix.

This will return the number of functions unregistered.

!SUBSUBSECTION Examples

  arangosh> require("org/arangodb/aql/functions").unregisterGroup("myfunctions::temperature");
  arangosh> require("org/arangodb/aql/functions").unregisterGroup("myfunctions");

To get an overview of which functions are currently registered, the toArray function can be used:

`aqlfunctions.toArray()`

Returns all previously registered AQL user functions, with their fully qualified names and function code.

The result may optionally be restricted to a specified group of functions by specifying a group prefix:

`aqlfunctions.toArray(prefix)`

!SUBSUBSECTION Examples

To list all available user functions:

  arangosh> require("org/arangodb/aql/functions").toArray();

To list all available user functions in the myfunctions namespace:

  arangosh> require("org/arangodb/aql/functions").toArray("myfunctions");

To list all available user functions in the myfunctions::temperature namespace:

  arangosh> require("org/arangodb/aql/functions").toArray("myfunctions::temperature");



<!--
@copydetails JSF_aqlfunctions_register

It is possible to unregister a single user function, or a whole group of
user functions (identified by their namespace) in one go:

@copydetails JSF_aqlfunctions_unregister

@copydetails JSF_aqlfunctions_unregister_group

To get an overview of which functions are currently registered, the 
`toArray` function can be used:

@copydetails JSF_aqlfunctions_toArray

-->