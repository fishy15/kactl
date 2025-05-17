/**
 * Author: Simon Lindholm
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: Add a new source $s'$ and sink $t'$, new edges from $s'$ to 
 * everything, and new edges from everything to $t'$. Define:
 * \begin{itemize}
 * \item $c'((s', v)) = \sum_{u \in V} d((u,v))$ for each edge $(s', v)$
 * \item $c'((v, t')) = \sum_{w \in V} d((v,w))$ for each edge $(v, t')$
 * \item $c'((u,v)) = c((u,v)) - d((u,v))$ for each old edge $(u, v)$
 * \item $c'((t,s)) = \infty$
 * \end{itemize}
 * Status: works
 */
