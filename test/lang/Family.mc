/*
 * @Class: Family
 * @Description: Sample Class file for Mate Programming 
 * 				 language using Class Syntax.
 * @Author: TOUBE P.Pierre 
 */
 namespace test;

class Family {
	public static const String CLASS_NAME = "Family";
	public String fatherName, motherName;
	public Array<String> childrenNames;
	static internal Number familyCount;
	static(){

	}
	
	Family(){}

	Family(Object data){
		motherName(data);
		fatherName(data,"Undefined");
		childrenNames(data,[]);
		familyCount++;
	}

	public static Number familyCount(){
		return familyCount;
	}

	/*
	 * Defaults getters and setters automatically managed by Mate.
	 * Some may override or restrict them.
	 */
}