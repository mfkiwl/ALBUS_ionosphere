cmake_minimum_required(VERSION 3.10)
project(sofa LANGUAGES Fortran C)

#---------------------------------------------------------------------------
# Version Numbers (customize as needed)
#---------------------------------------------------------------------------
set(VER_MAJOR 1)
set(VER_MINOR 0)
set(VER_SUBSUB 0)

#---------------------------------------------------------------------------
# List of Header Files to Install
#---------------------------------------------------------------------------
set(HEADERS
    sofa.h
)

#---------------------------------------------------------------------------
# List of Source Files
#
# These are all the Fortran source files from your Makefile.
#---------------------------------------------------------------------------
set(SRCS
    a2af.f
    a2tf.f
    anp.f
    anpm.f
    bi00.f
    bp00.f
    bpn2xy.f
    c2i00a.f
    c2i00b.f
    c2ibpn.f
    c2ixy.f
    c2ixys.f
    c2s.f
    c2t00a.f
    c2t00b.f
    c2tceo.f
    c2teqx.f
    c2tpe.f
    c2txy.f
    cal2jd.f
    cp.f
    cpv.f
    cr.f
    d2tf.f
    dat.f
    dtdb.f
    ee00.f
    ee00a.f
    ee00b.f
    eect00.f
    epb.f
    epb2jd.f
    epj.f
    epj2jd.f
    epv00.f
    eqeq94.f
    era00.f
    fk52h.f
    fk5hip.f
    fk5hz.f
    gmst00.f
    gmst82.f
    gst00a.f
    gst00b.f
    gst94.f
    h2fk5.f
    hfk5z.f
    ir.f
    jd2cal.f
    jdcalf.f
    num00a.f
    num00b.f
    numat.f
    nut00a.f
    nut00b.f
    nut80.f
    nutm80.f
    obl80.f
    p2pv.f
    p2s.f
    pap.f
    pas.f
    pdp.f
    plan94.f
    pm.f
    pmat00.f
    pmat76.f
    pmp.f
    pn.f
    pn00.f
    pn00a.f
    pn00b.f
    pnm00a.f
    pnm00b.f
    pnm80.f
    pom00.f
    ppp.f
    ppsp.f
    pr00.f
    prec76.f
    pv2p.f
    pv2s.f
    pvdpv.f
    pvm.f
    pvmpv.f
    pvppv.f
    pvstar.f
    pvu.f
    pvup.f
    pvxpv.f
    pxp.f
    rm2v.f
    rv2m.f
    rx.f
    rxp.f
    rxpv.f
    rxr.f
    ry.f
    rz.f
    s00.f
    s00a.f
    s00b.f
    s2c.f
    s2p.f
    s2pv.f
    s2xpv.f
    sepp.f
    seps.f
    sp00.f
    starpm.f
    starpv.f
    sxp.f
    sxpv.f
    tr.f
    trxp.f
    trxpv.f
    xys00a.f
    xys00b.f
    zp.f
    zpv.f
    zr.f
)

#---------------------------------------------------------------------------
# Build the Shared Library "sofa"
#
# This will generate a shared library libsofa.so with versioning.
#---------------------------------------------------------------------------
add_library(sofa SHARED ${SRCS})
set_target_properties(sofa PROPERTIES
    OUTPUT_NAME "sofa"
    VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_SUBSUB}"
    SOVERSION "${VER_MAJOR}"
)

# Link the math library; if your Fortran compiler requires an additional runtime
# library (e.g. g2c), add it here.
target_link_libraries(sofa PRIVATE m)

#---------------------------------------------------------------------------
# Installation Rules
#
# Install the shared library into the lib directory and the header into include.
#---------------------------------------------------------------------------
install(TARGETS sofa
    LIBRARY DESTINATION ${INSTALLDIR}/lib )
install(FILES ${HEADERS} DESTINATION ${INSTALLDIR}/include)


