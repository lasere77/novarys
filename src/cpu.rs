#[repr(C)]
enum RegsId {
    A = 0,
    C,
    D,
    R,
    F,
    X,
    RegIn,
    RegOut,
    NbReg,
}

#[derive(Clone, Copy)]
pub struct Byte(pub u8);

impl Byte {
    pub fn sign(self) -> i8 {
        self.0 as i8
    }

    pub fn unsign(self) -> u8 {
        self.0
    }

    pub fn set(&mut self, value: u8) {
        self.0 = value;
    }
}

pub struct Cpu {
    pub nv: u8,
    pub regs: [Byte; RegsId::NbReg as usize],
}

impl Cpu {
    pub fn init() -> Self {
        Self {
            nv: (0),
            regs: ([Byte(0); RegsId::NbReg as usize]),
        }
    }

    pub fn info(&self) {
        println!("tick: {}\n----", self.nv);
        println!("IN: {}", self.regs[RegsId::RegIn as usize].sign());
        println!("reg A: {}", self.regs[RegsId::A as usize].sign());
        println!("reg C: {}", self.regs[RegsId::C as usize].sign());
        println!("reg D: {}", self.regs[RegsId::D as usize].sign());
        println!("reg R: {}", self.regs[RegsId::R as usize].sign());
        println!("reg F: {}", self.regs[RegsId::F as usize].sign());
        println!("reg X: {}", self.regs[RegsId::X as usize].sign());
        println!("OUT: {}", self.regs[RegsId::RegOut as usize].sign());
        println!("----\n");
    }

    pub fn im(&mut self, value: u8) {
        println!("mode: im");
        println!("value: {}", value);
        self.regs[RegsId::A as usize].set(value);
    }

    pub fn alu(&mut self, instruction: u8) {
        println!("mode: alu");
        let logic_gate = instruction & 0b00000111;
        match logic_gate {
            0 => {
                println!("OR");
                self.regs[RegsId::R as usize].set(
                    self.regs[RegsId::C as usize].unsign() | self.regs[RegsId::D as usize].unsign(),
                );
            }
            1 => {
                println!("NAND");
                self.regs[RegsId::R as usize].set(
                    !(self.regs[RegsId::C as usize].unsign()
                        & self.regs[RegsId::D as usize].unsign()),
                );
            }
            2 => {
                println!("NOR");
                self.regs[RegsId::R as usize].set(
                    !(self.regs[RegsId::C as usize].unsign()
                        | self.regs[RegsId::D as usize].unsign()),
                );
            }
            3 => {
                println!("AND");
                self.regs[RegsId::R as usize].set(
                    self.regs[RegsId::C as usize].unsign() & self.regs[RegsId::D as usize].unsign(),
                );
            }
            4 => {
                println!("ADD");
                self.regs[RegsId::R as usize].set(
                    self.regs[RegsId::C as usize]
                        .unsign()
                        .wrapping_add(self.regs[RegsId::D as usize].unsign()),
                );
            }
            5 => {
                println!("SUB");
                self.regs[RegsId::R as usize].set(
                    self.regs[RegsId::C as usize]
                        .unsign()
                        .wrapping_sub(self.regs[RegsId::D as usize].unsign()),
                );
            }
            _ => todo!(),
        }
    }

    pub fn copy(&mut self, instruction: u8) {
        println!("mode: copy");
        let input = (instruction & 0b00111000) >> 3;
        let output = instruction & 0b00000111;
        if output == 0b00000110 {
            self.regs[RegsId::RegOut as usize] = self.regs[input as usize];
        } else {
            self.regs[output as usize] = self.regs[input as usize];
        }
    }

    pub fn condition(&mut self, instruction: u8) {
        println!("mode: condition");
        let condition = instruction & 0b00000111;
        let need_jump: bool;
        match condition {
            0 => need_jump = false,
            1 => need_jump = self.regs[RegsId::R as usize].sign() == 0,
            2 => need_jump = self.regs[RegsId::R as usize].sign() < 0,
            3 => need_jump = self.regs[RegsId::R as usize].sign() <= 0,
            4 => need_jump = true,
            5 => need_jump = self.regs[RegsId::R as usize].sign() != 0,
            6 => need_jump = self.regs[RegsId::R as usize].sign() >= 0,
            7 => need_jump = self.regs[RegsId::R as usize].sign() > 0,
            _ => todo!(),
        }
        if need_jump {
            println!("jump at: {}", self.regs[RegsId::A as usize].unsign() - 1);
            self.nv = self.regs[RegsId::A as usize].unsign() - 1;
        }
    }
}
