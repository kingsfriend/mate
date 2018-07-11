/*
 * @Template Family
 * @Description sample script template for Mate Programming language
 * @Author TOUBE P.Pierre 
 *
 */
namespace test;

use lang.String as String, lang.Array;
use lang.Number;

@template(test.Family)
class Family extends Object{
	static internal Number familiesCount;
	String fatherName, motherName;
	Array<String> childrenNames;
	
	// Object constructor
	Family (String fatherName, String motherName){
		up().fatherName = fatherName;
		up().motherName = motherName;
		childrenNames = new Array();
		familiesCount++;
	}

	// Getters and setters automatically managed

	addChildName(String childName){
		childrenNames.push(childName);
	} 

	// Object destructor
	@Family(){
		familiesCount++;
	}

	@static Class(){

	}
}