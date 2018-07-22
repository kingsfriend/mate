@/*
  * @Template Family
  * @Description sample script template for Mate Programming language using Scripting Syntax
  * @Author TOUBE P.Pierre 
  *
  */
@namespace(test)

@use(String)

@require(String var1, var2)
@require(Number familiesCount)

@var(String fatherName, motherName=@"Lee")
@var(Bool hasChild=true)
@var(Array childrenNames = [])
@var(Object mateLang = {})

@value(fatherName=@"Bruce P.")
@value(hasChild=true, childrenNames=[@"Cedric", @"Martin", @"Pierre", @"Lea"])

@define( Family )
Family Description
==================
@value(mateLang= { nom:@"Mate", description :@"Programming Lang", keyords:[@"mate", 155, true]} )

    Father's Name: @(fatherName) @\
    Mother's Name: @(motherName, @"Nothing to display") @\
	Number of child: @(childrenNamesCount, 0) @// valuation operator is null safe

	@@include( ChildrenSection, { @@fatherName = 1, @@motherName = @@"bla" })

	List of children's names
	------------------------
@	@foreach( childName : childrenNames )
		> @(childName)
		@break @
		@continue @
	@empty 
		> there is no child name to display.
	@end 
	