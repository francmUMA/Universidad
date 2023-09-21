function solve_ec_line(a)
    for i = 1:size(a, 1)
        for j = 1:size(a(i), 1)
            fprintf('%dx%d ', a(i,j),j);
        end
        fprintf('\n');
    end
end

