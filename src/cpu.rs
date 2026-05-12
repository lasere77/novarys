
#[repr(C)]
enum RegsId {
    A,
    C,
    D,
    R,
    F,
    X,
    RegIn,
    RegOut,
    NbReg,
}

#[repr(C)]
#[derive(Clone, Copy)]
pub union Byte {
    i_byte: i8,
    u_byte: u8,
}

pub struct Cpu {
    pub nv:     u8,
    pub regs:   [Byte; RegsId::NbReg as usize],
}

impl Cpu {
    pub fn init() -> Self
    {
        Self { 
            nv: (0),
            regs: ([Byte {i_byte: 0}; RegsId::NbReg as usize])
        }
    }

    pub fn info(&self) {
        println!("tick: {}\n----", self.nv);
        unsafe {
            println!("IN {}", self.regs[RegsId::RegIn as usize].i_byte);
            println!("reg A {}", self.regs[RegsId::A as usize].i_byte);
            println!("reg C {}", self.regs[RegsId::C as usize].i_byte);
            println!("reg D {}", self.regs[RegsId::D as usize].i_byte);
            println!("reg R {}", self.regs[RegsId::R as usize].i_byte);
            println!("reg F {}", self.regs[RegsId::F as usize].i_byte);
            println!("reg X {}", self.regs[RegsId::X as usize].i_byte);
            println!("OUT {}", self.regs[RegsId::RegOut as usize].i_byte);
        }
        println!("----\n");
    }

    pub fn  im(&mut self, value: u8) {
        println!("mode: im");
        self.regs[RegsId::A as usize].u_byte = value;
    }

    pub fn alu(&mut self, instruction: u8) {
        println!("mode: alu");
        let logic_gate = instruction & 0b00000111;
        match logic_gate {
            0 => self.regs[RegsId::R as usize].i_byte = unsafe {self.regs[RegsId::C as usize].i_byte | self.regs[RegsId::D as usize].i_byte},
            1 => self.regs[RegsId::R as usize].i_byte = unsafe {!(self.regs[RegsId::C as usize].i_byte & self.regs[RegsId::D as usize].i_byte)},
            2 => self.regs[RegsId::R as usize].i_byte = unsafe {!(self.regs[RegsId::C as usize].i_byte | self.regs[RegsId::D as usize].i_byte)},
            3 => self.regs[RegsId::R as usize].i_byte = unsafe {self.regs[RegsId::C as usize].i_byte & self.regs[RegsId::D as usize].i_byte},
            4 => self.regs[RegsId::R as usize].i_byte = unsafe {self.regs[RegsId::C as usize].i_byte + self.regs[RegsId::D as usize].i_byte},
            5 => self.regs[RegsId::R as usize].i_byte = unsafe {self.regs[RegsId::C as usize].i_byte - self.regs[RegsId::D as usize].i_byte},
            _ => todo!(),
        }
    }

    pub fn copy(&mut self, instruction: u8) {
        println!("mode: copy");
        let input = instruction & 0b00111000;
        let output = instruction & 0b00000111;
        if output == 0b00000110
        {
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
            1 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte == 0 },
            2 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte < 0 },
            3 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte <= 0 },
            4 => need_jump = true,
            5 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte != 0 },
            6 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte >= 0 },
            7 => need_jump = unsafe { self.regs[RegsId::R as usize].i_byte > 0 },
            _ => todo!(),
        }
        if need_jump {
            unsafe {
                println!("jump at: {}", self.regs[RegsId::A as usize].u_byte - 1);
                self.nv =  self.regs[RegsId::A as usize].u_byte - 1;
            }
        }
    }
}
