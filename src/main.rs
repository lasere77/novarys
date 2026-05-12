mod cpu;
mod rom;

fn main() {
    let rom: [u8; rom::ROM_SIZE] = rom::get_rom();
    let mut cpu = cpu::Cpu::init();

    while usize::from(cpu.nv) != rom::ROM_SIZE
    {
        let instruction = rom.get(usize::from(cpu.nv)).unwrap();
        let opcode: u8 = instruction & 0b11000000;
        match opcode {
            0 => cpu.im(*instruction),
            64 => cpu.alu(*instruction),
            128 => cpu.copy(*instruction),
            192 => cpu.condition(*instruction),
            _ => panic!(),
        }
        cpu.info();
        cpu.nv += 1;
    }
}
