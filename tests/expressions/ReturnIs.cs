class Foo {
    ISymbol ITypeSymbol.FindImplementationForInterfaceMember(ISymbol interfaceMember)
    {
        return interfaceMember is Symbol
            ? FindImplementationForInterfaceMember((Symbol)interfaceMember)
            : null;
    }
}
