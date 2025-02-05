static int
opMOVD_l_mm_a16(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVD_l_xmm_a16(fetchdat);

    MMX_ENTER();

    fetch_ea_16(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_reg].l[0] = cpu_state.regs[cpu_rm].l;
        cpu_state.MM[cpu_reg].l[1] = 0;
        CLOCK_CYCLES(1);
    } else {
        uint32_t dst;

        SEG_CHECK_READ(cpu_state.ea_seg);
        dst = readmeml(easeg, cpu_state.eaaddr);
        if (cpu_state.abrt)
            return 1;
        cpu_state.MM[cpu_reg].l[0] = dst;
        cpu_state.MM[cpu_reg].l[1] = 0;

        CLOCK_CYCLES(2);
    }
    return 0;
}
static int
opMOVD_l_mm_a32(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVD_l_xmm_a32(fetchdat);

    MMX_ENTER();

    fetch_ea_32(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_reg].l[0] = cpu_state.regs[cpu_rm].l;
        cpu_state.MM[cpu_reg].l[1] = 0;
        CLOCK_CYCLES(1);
    } else {
        uint32_t dst;

        SEG_CHECK_READ(cpu_state.ea_seg);
        dst = readmeml(easeg, cpu_state.eaaddr);
        if (cpu_state.abrt)
            return 1;
        cpu_state.MM[cpu_reg].l[0] = dst;
        cpu_state.MM[cpu_reg].l[1] = 0;

        CLOCK_CYCLES(2);
    }
    return 0;
}

static int
opMOVD_mm_l_a16(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVD_xmm_l_a16(fetchdat);

    MMX_ENTER();

    fetch_ea_16(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.regs[cpu_rm].l = cpu_state.MM[cpu_reg].l[0];
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 3);
        writememl(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].l[0]);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}
static int
opMOVD_mm_l_a32(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVD_xmm_l_a32(fetchdat);

    MMX_ENTER();

    fetch_ea_32(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.regs[cpu_rm].l = cpu_state.MM[cpu_reg].l[0];
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 3);
        writememl(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].l[0]);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}

#if defined(DEV_BRANCH) && defined(USE_CYRIX_6X86)
/*Cyrix maps both MOVD and SMINT to the same opcode*/
static int
opMOVD_mm_l_a16_cx(uint32_t fetchdat)
{
    if (in_smm)
        return opSMINT(fetchdat);

    MMX_ENTER();

    fetch_ea_16(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.regs[cpu_rm].l = cpu_state.MM[cpu_reg].l[0];
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 3);
        writememl(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].l[0]);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}
static int
opMOVD_mm_l_a32_cx(uint32_t fetchdat)
{
    if (in_smm)
        return opSMINT(fetchdat);

    MMX_ENTER();

    fetch_ea_32(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.regs[cpu_rm].l = cpu_state.MM[cpu_reg].l[0];
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 3);
        writememl(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].l[0]);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}
#endif

static int
opMOVQ_q_mm_a16(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVDQA_l_xmm_a16(fetchdat);

    MMX_ENTER();

    fetch_ea_16(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_reg].q = cpu_state.MM[cpu_rm].q;
        CLOCK_CYCLES(1);
    } else {
        uint64_t dst;

        SEG_CHECK_READ(cpu_state.ea_seg);
        dst = readmemq(easeg, cpu_state.eaaddr);
        if (cpu_state.abrt)
            return 1;
        cpu_state.MM[cpu_reg].q = dst;
        CLOCK_CYCLES(2);
    }
    return 0;
}
static int
opMOVQ_q_mm_a32(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVDQA_l_xmm_a32(fetchdat);

    MMX_ENTER();

    fetch_ea_32(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_reg].q = cpu_state.MM[cpu_rm].q;
        CLOCK_CYCLES(1);
    } else {
        uint64_t dst;

        SEG_CHECK_READ(cpu_state.ea_seg);
        dst = readmemq(easeg, cpu_state.eaaddr);
        if (cpu_state.abrt)
            return 1;
        cpu_state.MM[cpu_reg].q = dst;
        CLOCK_CYCLES(2);
    }
    return 0;
}

static int
opMOVQ_mm_q_a16(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVDQA_xmm_q_a16(fetchdat);

    MMX_ENTER();

    fetch_ea_16(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_rm].q = cpu_state.MM[cpu_reg].q;
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 7);
        writememq(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].q);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}
static int
opMOVQ_mm_q_a32(uint32_t fetchdat)
{
    if ((cpu_features & CPU_FEATURE_SSE2) && sse_xmm)
        return opMOVDQA_xmm_q_a32(fetchdat);

    MMX_ENTER();

    fetch_ea_32(fetchdat);
    if (cpu_mod == 3) {
        cpu_state.MM[cpu_rm].q = cpu_state.MM[cpu_reg].q;
        CLOCK_CYCLES(1);
    } else {
        SEG_CHECK_WRITE(cpu_state.ea_seg);
        CHECK_WRITE_COMMON(cpu_state.ea_seg, cpu_state.eaaddr, cpu_state.eaaddr + 7);
        writememq(easeg, cpu_state.eaaddr, cpu_state.MM[cpu_reg].q);
        if (cpu_state.abrt)
            return 1;
        CLOCK_CYCLES(2);
    }
    return 0;
}
