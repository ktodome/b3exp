# x = df.index
# y = df.n
def rebin(x,y):
    bins = len(x)-1
    ndiv = 8
    assert bins%ndiv ==0 
    bins_new = int(bins/ndiv)
    print(bins_new)
    dx=x[1]-x[0]
    x_new = np.linspace(x[0],x[-1],bins_new+1)
    y_new = [np.sum(y[i*ndiv:(i+1)*ndiv]) for i in range(bins_new+1)]
    return x_new, y_new
    # print(x_new,y_new)
    # print(len(x_new))
    # print(len(y_new))
