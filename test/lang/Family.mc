/*
 * @Class: Family
 * @Description: Sample Class file for Mate Programming 
 * 				 language using Class Syntax.
 * @Author: TOUBE P.Pierre 
 */
 namespace test;

@Template(Family)
class Family {
	public String fatherName, motherName;
	public Array childrenNames;
	static internal Number familyCount;

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