interval = setInterval('{', 10);
setTimeout(function(){
    clearInterval(interval);
    t.step(function(){
        assert_true(ran, 'ran');
        t.done();
    });
    t_col.step(col_check);
}, 20);