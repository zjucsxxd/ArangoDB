/*jslint indent: 2, nomen: true, maxlen: 100, sloppy: true, vars: true, white: true, plusplus: true */
/*global require, exports, Graph, arguments */

////////////////////////////////////////////////////////////////////////////////
/// @brief Graph Data for Example
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2014 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Michael Hackstein
/// @author Copyright 2011-2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////
(function() {

  var Graph = require("org/arangodb/general-graph");

  var createSocialGraph = function() {
    var edgeDefinition = [];
    edgeDefinition.push(Graph._undirectedRelationDefinition("relation", ["female", "male"]));
    var g = Graph._create("social", edgeDefinition);
    var a = g.female.save({name: "Alice"});
    var b = g.male.save({name: "Bob"});
    var c = g.male.save({name: "Charly"});
    var d = g.female.save({name: "Diana"});
    g.relation.save(a._id, b._id, {type: "married"});
    g.relation.save(a._id, c._id, {type: "friend"});
    g.relation.save(c._id, d._id, {type: "married"});
    g.relation.save(b._id, d._id, {type: "friend"});
    return g;
  };

  var loadGraph = function(name) {
    if (Graph._exists(name)) {
      return Graph._graph(name);
    }
    switch (name) {
      case "social":
        return createSocialGraph();
    }

  };

  var dropGraph = function(name) {
    return Graph._drop(name);
  };

  exports.loadGraph = loadGraph;
  exports.dropGraph = dropGraph;
}());