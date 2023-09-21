function[solv] = solve_ec_line(a, e)
    for i = 1:size(a,1)
        fprintf('%s = %f\n', mat2str(a(i,:)), e(i));
    end
    solv = a\e;
end

