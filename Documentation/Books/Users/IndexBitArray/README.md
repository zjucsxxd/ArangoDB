!CHAPTER BitArray Indexes

!SUBSECTION Introduction to Bit-Array Indexes

It is possible to define a bit-array index on one or more attributes (or paths)
of a documents.

!SUBSECTION Accessing BitArray Indexes from the Shell

`collection.ensureBitarray( field1, value1, ..., fieldn, valuen)`

Creates a bitarray index on documents using attributes as paths to the fields ( field1,..., fieldn). A value ( value1,..., valuen) consists of an array of possible values that the field can take. At least one field and one set of possible values must be given.

All documents, which do not have all of the attribute paths are ignored (that is, are not part of the bitarray index, they are however stored within the collection). A document which contains all of the attribute paths yet has one or more values which are not part of the defined range of values will be rejected and the document will not inserted within the collection. Note that, if a bitarray index is created subsequent to any documents inserted in the given collection, then the creation of the index will fail if one or more documents are rejected (due to attribute values being outside the designated range).

In case that the index was successfully created, the index identifier is returned.

In the example below we create a bitarray index with one field and that field can have the values of either 0 or 1. Any document which has the attribute x defined and does not have a value of 0 or 1 will be rejected and therefore not inserted within the collection. Documents without the attribute x defined will not take part in the index.

  arango> arangod> db.example.ensureBitarray("x", [0,1]);
  {
  "id" : "2755894/3607862",
  "unique" : false,
  "type" : "bitarray",
  "fields" : [["x", [0, 1]]],
  "undefined" : false,
  "isNewlyCreated" : true
  }

In the example below we create a bitarray index with one field and that field can have the values of either 0, 1 or other (indicated by []). Any document which has the attribute x defined will take part in the index. Documents without the attribute x defined will not take part in the index.

  arangod> db.example.ensureBitarray("x", [0,1,[]]);
  {
  "id" : "2755894/4263222",
  "unique" : false,
  "type" : "bitarray",
  "fields" : [["x", [0, 1, [ ]]]],
  "undefined" : false,
  "isNewlyCreated" : true
  }

In the example below we create a bitarray index with two fields. Field x can have the values of either 0 or 1; while field y can have the values of 2 or "a". A document which does not have both attributes x and y will not take part within the index. A document which does have both attributes x and y defined must have the values 0 or 1 for attribute x and 2 or a for attribute y, otherwise the document will not be inserted within the collection.

  arangod> db.example.ensureBitarray("x", [0,1], "y", [2,"a"]);
  {
  "id" : "2755894/5246262",
  "unique" : false,
  "type" : "bitarray",
  "fields" : [["x", [0, 1]], ["y", [0, 1]]],
  "undefined" : false,
  "isNewlyCreated" : false
  }

In the example below we create a bitarray index with two fields. Field x can have the values of either 0 or 1; while field y can have the values of 2, "a" or other . A document which does not have both attributes x and y will not take part within the index. A document which does have both attributes x and y defined must have the values 0 or 1 for attribute x and any value for attribute y will be acceptable, otherwise the document will not be inserted within the collection.

  arangod> db.example.ensureBitarray("x", [0,1], "y", [2,"a",[]]);
  {
  "id" : "2755894/5770550",
  "unique" : false,
  "type" : "bitarray",
  "fields" : [["x", [0, 1]], ["y", [2, "a", [ ]]]],
  "undefined" : false,
  "isNewlyCreated" : true
  }

<!--
@anchor IndexBitArrayShellEnsureBitarray
@copydetails JSF_ArangoCollection_prototype_ensureBitarray
-->