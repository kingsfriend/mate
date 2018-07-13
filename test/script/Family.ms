@/*
  * @Template Family
  * @Description sample script template for Mate Programming language
  * @Author TOUBE P.Pierre 
  *
  */
@namespace(test)

@use(lang)

@require(String fatherName, motherName)
@require(Array childrenNames)

@require(Number familiesCount)
@define( Family )
Family Description
==================

    Father's Name: @(fatherName) @\
    Mother's Name: @(motherName) @@\
	Number of child: @(childrenNamesCount,0) @// valuation operator is null safe

	@@include( ChildrenSection, { @fatherName = 1, @motherName = "bla" })

	List of children's names
	------------------------
@	@foreach( childName : childrenNames )
		> @(childName)
		@break(21)
		@continue(3)
	@empty 
		> there is no child name to display.
	@end 
	