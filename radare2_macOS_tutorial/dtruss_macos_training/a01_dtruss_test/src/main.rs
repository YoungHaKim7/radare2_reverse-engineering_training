fn main() {
    let my_string = String::from("Hello, Rust!");

    // Convert the String to a Vec<u8>
    let string_as_u8: Vec<u8> = my_string.into_bytes();

    // Print the result
    println!("{:?}", string_as_u8);
}
