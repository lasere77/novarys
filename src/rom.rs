use std::io::Read;

const NOP_OPCODE: u8 = 192;
pub const ROM_SIZE: usize = 255;

pub fn get_rom() -> [u8; ROM_SIZE] {
    let file_path: String = std::env::args()
        .nth(1)
        .expect("Please set the path to the binary file.");
    let file =
        std::fs::File::open(file_path).expect("Fail to open the file, Please check the path");
    let mut reader = std::io::BufReader::new(file);
    let mut rom: [u8; ROM_SIZE] = [NOP_OPCODE; ROM_SIZE];
    if reader.read(&mut rom).unwrap() > ROM_SIZE {
        println!(
            "Warning: Please note that the binary file contains more data than the ROM can hold."
        );
    }
    rom
}
