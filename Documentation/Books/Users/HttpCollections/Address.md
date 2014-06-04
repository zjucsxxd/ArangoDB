!CHAPTER Address of a Collection

All collections in ArangoDB have an unique identifier and a unique
name. ArangoDB internally uses the collection's unique identifier to
look up collections. This identifier however is managed by ArangoDB
and the user has no control over it. In order to allow users use their
own names, each collection also has a unique name, which is specified
by the user.  To access a collection from the user perspective, the
collection name should be used, i.e.:

    http://server:port/_api/collection/collection-name

For example: Assume that the collection identifier is `7254820` and
the collection name is `demo`, then the URL of that collection is:

    http://localhost:8529/_api/collection/demo
