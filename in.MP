

units                   metal
atom_style              atomic
boundary                p p p

read_data ../coexisting_Al.data

pair_style      eam/alloy
pair_coeff * * ../Mishin-Ni-Al-2009.eam.alloy Al

timestep 0.0025

neighbor                2.0 bin
neigh_modify            delay 5 check yes

thermo 100



variable TT equal 500



fix 3 all npt temp ${TT} ${TT} 0.05 iso 0.0 0.0 0.05 drag 0.2
run 80000
unfix 3

    compute myrdf all rdf 100 1 1
    fix 4 all ave/time 1 1 1 c_myrdf file Al_${TT}.rdf mode vector
     run 0 
    unfix 4



dump     1 all cfg 1 Al_${TT}_*.cfg id type xs ys zs
dump_modify 1 element Al
run                     0
undump 1

write_restart ${TT}.restart

