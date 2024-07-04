package dev.pimous.javautils;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;

/** Gives an overriding of the {@code toString} method. It's based on
 * introspection of non-static implementing class's fields.<br><br>
 * 
 * Be carefull about recursivity when {@link toString} calling makes a loop. For
 * example, when an {@code Object} wants to represent one of its field that
 * needs also to represent one of its fields that contains the first one (Or
 * something similar).
 * 
 * <pre>
 *class A extends AutoToString{
 *    private B object;
 *}
 * 
 *class B extends AutoToString{
 *    private A object;
 *}
 * </pre>
 * 
 * That will end up in filling the stack. {@link createString} can helps you in
 * this case.<br><br>
 * 
 * <i>Licensed under <a href="https://www.gnu.org/licenses/lgpl+gpl-3.0.txt">
 * GNU LGPL-3.0</a></i>.
 * @version 1.1.2
 * @author xibitol
 */
public abstract class AutoToString {

	/** Generates a {@code String} representation of the implementing class.
	 * It's based on an introspection of the given non-static {@code fields}.
	 * 
	 * @param fields Fields to include in the representation.
	 * @return The {@link String} representation of this object with the
	 * {@code fields} given.
	 * @since 1.1.0
	 */
	protected String createString(Field[] fields){
		String end = ", ";

		StringBuilder sb = new StringBuilder(this.getClass().getName() + "{");
		for(Field f : fields){
			if(!Modifier.isStatic(f.getModifiers())){
				sb.append(f.getName());
				sb.append("=");

				f.setAccessible(true); // BUG: Is this can fail ?
				try{ sb.append(f.get(this)); }catch(Exception ignored){}

				sb.append(end);
			}
		}
		sb.replace(sb.length() - end.length(), sb.length(), "}");

		return sb.toString();
	}

	@Override
	public String toString(){
		return createString(this.getClass().getDeclaredFields());
	}
}