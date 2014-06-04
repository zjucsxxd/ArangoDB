!CHAPTER Importing Headers and Values

When using this type of import, the attribute names of the documents to be
imported are specified separate from the actual document value data.  The first
line of the HTTP POST request body must be a JSON list containing the attribute
names for the documents that follow.  The following lines are interpreted as the
document data. Each document must be a JSON list of values. No attribute names
are needed or allowed in this data section.

@EXAMPLES

@verbinclude api-import-headers

The server will again respond with an HTTP 201 if everything went well. The
number of documents imported will be returned in the `created` attribute of the
response. If any documents were skipped or incorrectly formatted, this will be
returned in the `errors` attribute. The number of empty lines in the input file
will be returned in the `empty` attribute.

If the `details` parameter was set to `true` in the request, the response will 
also contain an attribute `details` which is a list of details about errors that
occurred on the server side during the import. This list might be empty if no
errors occurred.
