import React, { useState, useMemo } from 'react';
import { 
  Search, Zap, Wind, Cog, Link2, Cpu, 
  Wrench, Plus, Minus, MapPin, AlertTriangle, 
  X, Check, Package, User
} from 'lucide-react';

// Dados fictícios super detalhados para simular o ambiente real da manutenção
const initialInventory = [
  {
    id: 1,
    name: 'Parafuso Sextavado Inox',
    sku: 'FIX-M8-001',
    category: 'Elementos de Fixação',
    specs: 'M8 x 20mm',
    location: 'Corredor A > Estante 3 > Gaveta 12',
    qty: 45,
    minQty: 50,
  },
  {
    id: 2,
    name: 'Contator Trifásico',
    sku: 'ELE-WEG-022',
    category: 'Componentes Elétricos',
    specs: '32A 24VDC CWB32',
    location: 'Corredor B > Armário 1 > Prateleira 2',
    qty: 12,
    minQty: 5,
  },
  {
    id: 3,
    name: 'Cilindro ISO Dupla Ação',
    sku: 'PNE-FESTO-10',
    category: 'Componentes Pneumáticos',
    specs: 'DNC-32-100-PPV-A',
    location: 'Corredor C > Estante 1 > Caixa Azul',
    qty: 2,
    minQty: 4,
  },
  {
    id: 4,
    name: 'Rolamento Rígido de Esferas',
    sku: 'MEC-SKF-6204',
    category: 'Componentes Mecânicos',
    specs: '6204-2Z',
    location: 'Corredor A > Estante 4 > Gaveta 05',
    qty: 8,
    minQty: 10,
  },
  {
    id: 5,
    name: 'CLP S7-1200',
    sku: 'ELT-SIEMENS-1214',
    category: 'Equipamentos Eletrônicos',
    specs: 'CPU 1214C DC/DC/DC',
    location: 'Sala Cofre > Armário Eletrônica > Prateleira 1',
    qty: 3,
    minQty: 2,
  },
  {
    id: 6,
    name: 'Chave Combinada',
    sku: 'FER-BELZER-13',
    category: 'Ferramentas & Consumíveis',
    specs: '13mm Cromo Vanádio',
    location: 'Painel de Ferramentas Principal > Linha 2',
    qty: 4,
    minQty: 2,
  },
  {
    id: 7,
    name: 'Porca Autotravante M8',
    sku: 'FIX-M8-002',
    category: 'Elementos de Fixação',
    specs: 'M8 Aço Inox 304',
    location: 'Corredor A > Estante 3 > Gaveta 13',
    qty: 200,
    minQty: 100,
  },
  {
    id: 8,
    name: 'Válvula Solenoide 5/2 vias',
    sku: 'PNE-SMC-52',
    category: 'Componentes Pneumáticos',
    specs: 'SY5120-5LZD-01 24VDC',
    location: 'Corredor C > Estante 2 > Gaveta 02',
    qty: 1,
    minQty: 3,
  }
];

const categories = [
  { name: 'Componentes Elétricos', icon: Zap, color: 'bg-yellow-100 text-yellow-700 border-yellow-200' },
  { name: 'Componentes Pneumáticos', icon: Wind, color: 'bg-sky-100 text-sky-700 border-sky-200' },
  { name: 'Componentes Mecânicos', icon: Cog, color: 'bg-slate-200 text-slate-700 border-slate-300' },
  { name: 'Elementos de Fixação', icon: Link2, color: 'bg-stone-200 text-stone-700 border-stone-300' },
  { name: 'Equipamentos Eletrônicos', icon: Cpu, color: 'bg-purple-100 text-purple-700 border-purple-200' },
  { name: 'Ferramentas & Consumíveis', icon: Wrench, color: 'bg-orange-100 text-orange-700 border-orange-200' },
];

export default function BiotropInventory() {
  const [inventory, setInventory] = useState(initialInventory);
  const [searchTerm, setSearchTerm] = useState('');
  const [activeCategory, setActiveCategory] = useState(null);
  
  // Controle do Modal de Movimentação (Substitui o alert/prompt)
  const [modalState, setModalState] = useState({
    isOpen: false,
    item: null,
    actionType: 'add', // 'add' ou 'remove'
    operatorName: '',
    quantity: 1
  });

  const filteredInventory = useMemo(() => {
    return inventory.filter(item => {
      const matchesCategory = activeCategory ? item.category === activeCategory : true;
      const searchLower = searchTerm.toLowerCase();
      const matchesSearch = 
        item.name.toLowerCase().includes(searchLower) ||
        item.sku.toLowerCase().includes(searchLower) ||
        item.specs.toLowerCase().includes(searchLower) ||
        item.category.toLowerCase().includes(searchLower);
      
      return matchesCategory && matchesSearch;
    });
  }, [inventory, searchTerm, activeCategory]);

  const handleOpenModal = (item, type) => {
    setModalState({
      isOpen: true,
      item,
      actionType: type,
      operatorName: '',
      quantity: 1
    });
  };

  const handleConfirmMovement = (e) => {
    e.preventDefault();
    if (!modalState.operatorName.trim()) return;

    setInventory(prev => prev.map(item => {
      if (item.id === modalState.item.id) {
        const qtyChange = parseInt(modalState.quantity, 10);
        const newQty = modalState.actionType === 'add' 
          ? item.qty + qtyChange 
          : Math.max(0, item.qty - qtyChange); // Não permite estoque negativo
        return { ...item, qty: newQty };
      }
      return item;
    }));
    
    // Reset e fecha modal
    setModalState(prev => ({ ...prev, isOpen: false }));
  };

  return (
    <div className="min-h-screen bg-stone-50 text-stone-800 font-sans selection:bg-green-200">
      
      {/* Topbar Corporativa Biotrop */}
      <header className="bg-green-800 text-white shadow-md sticky top-0 z-30">
        <div className="max-w-7xl mx-auto px-4 py-4 flex flex-col md:flex-row items-center justify-between gap-4">
          <div className="flex items-center gap-3">
            <div className="bg-white p-2 rounded-lg">
              <Package className="w-8 h-8 text-green-700" />
            </div>
            <div>
              <h1 className="text-2xl font-bold tracking-tight">BIOTROP <span className="font-light">CAMM 3</span></h1>
              <p className="text-green-200 text-sm font-medium tracking-wide uppercase">Controle de Estoque de Manutenção</p>
            </div>
          </div>
          
          {/* Barra de Busca Gigante (Prioridade #1 de Usabilidade) */}
          <div className="w-full md:w-1/2 relative">
            <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none">
              <Search className="h-6 w-6 text-green-700" />
            </div>
            <input
              type="text"
              className="block w-full pl-12 pr-4 py-4 border-2 border-transparent rounded-xl text-lg text-stone-900 bg-white placeholder-stone-400 focus:outline-none focus:ring-4 focus:ring-green-400 focus:border-green-600 transition-all shadow-sm"
              placeholder="Buscar peça, código (SKU) ou medida (ex: M8x20)..."
              value={searchTerm}
              onChange={(e) => setSearchTerm(e.target.value)}
            />
            {searchTerm && (
              <button 
                onClick={() => setSearchTerm('')}
                className="absolute inset-y-0 right-0 pr-4 flex items-center text-stone-400 hover:text-stone-600"
              >
                <X className="h-5 w-5" />
              </button>
            )}
          </div>
        </div>
      </header>

      <main className="max-w-7xl mx-auto px-4 py-8">
        
        {}
        <section className="mb-10">
          <h2 className="text-xl font-bold text-stone-700 mb-4 flex items-center gap-2">
            Categorias de Peças
            {activeCategory && (
              <button 
                onClick={() => setActiveCategory(null)}
                className="ml-2 text-sm bg-stone-200 hover:bg-stone-300 text-stone-700 px-3 py-1 rounded-full flex items-center gap-1 transition-colors"
              >
                Limpar Filtro <X className="w-3 h-3" />
              </button>
            )}
          </h2>
          <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-6 gap-3">
            {categories.map(cat => {
              const Icon = cat.icon;
              const isActive = activeCategory === cat.name;
              return (
                <button
                  key={cat.name}
                  onClick={() => setActiveCategory(isActive ? null : cat.name)}
                  className={`flex flex-col items-center justify-center p-4 rounded-2xl border-2 transition-all duration-200
                    ${isActive 
                      ? 'border-green-600 bg-green-50 shadow-md transform scale-105' 
                      : 'border-stone-200 bg-white hover:border-green-400 hover:shadow-sm'
                    }
                  `}
                >
                  <div className={`p-3 rounded-full mb-3 ${cat.color}`}>
                    <Icon className="w-8 h-8" />
                  </div>
                  <span className="text-sm font-semibold text-center leading-tight">
                    {cat.name}
                  </span>
                </button>
              );
            })}
          </div>
        </section>

        {}
        <section>
          <div className="flex justify-between items-end mb-4">
            <h2 className="text-2xl font-bold text-stone-800">
              Itens em Estoque ({filteredInventory.length})
            </h2>
          </div>
          
          {filteredInventory.length === 0 ? (
            <div className="bg-white rounded-2xl p-12 text-center border border-stone-200 shadow-sm">
              <Package className="w-16 h-16 text-stone-300 mx-auto mb-4" />
              <h3 className="text-xl font-bold text-stone-600">Nenhum item encontrado</h3>
              <p className="text-stone-500 mt-2">Tente buscar por outro termo ou limpar os filtros de categoria.</p>
            </div>
          ) : (
            <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-2 xl:grid-cols-3 gap-6">
              {filteredInventory.map(item => {
                const isLowStock = item.qty <= item.minQty;
                
                return (
                  <div 
                    key={item.id} 
                    className={`relative bg-white rounded-2xl p-5 border-2 transition-shadow hover:shadow-lg flex flex-col h-full
                      ${isLowStock ? 'border-red-300 bg-red-50/30' : 'border-stone-200'}
                    `}
                  >
                    {/* Alerta Visual de Estoque Baixo */}
                    {isLowStock && (
                      <div className="absolute -top-3 -right-3 bg-red-100 text-red-700 border border-red-200 px-3 py-1 rounded-full text-xs font-bold flex items-center gap-1 shadow-sm">
                        <AlertTriangle className="w-3 h-3" />
                        Repor Estoque
                      </div>
                    )}

                    <div className="flex gap-4 mb-4">
                      {/* Placeholder para foto (Como pedido) */}
                      <div className="w-24 h-24 bg-stone-100 rounded-xl border border-stone-200 flex-shrink-0 flex items-center justify-center">
                        <Package className="w-8 h-8 text-stone-300" />
                      </div>
                      
                      <div className="flex-1">
                        <p className="text-xs font-bold text-green-700 mb-1 uppercase tracking-wider">{item.sku}</p>
                        <h3 className="text-lg font-bold text-stone-800 leading-tight mb-1">{item.name}</h3>
                        <p className="text-sm font-semibold text-stone-500">{item.specs}</p>
                        <span className="inline-block mt-2 px-2 py-1 bg-stone-100 text-stone-600 text-xs rounded-md border border-stone-200">
                          {item.category}
                        </span>
                      </div>
                    </div>

                    {/* Mapeamento Físico Super Visível (Crucial para Usabilidade) */}
                    <div className="bg-amber-50 border border-amber-200 rounded-lg p-3 mb-4 flex items-start gap-2">
                      <MapPin className="w-5 h-5 text-amber-600 mt-0.5 flex-shrink-0" />
                      <div>
                        <p className="text-xs text-amber-700 font-bold uppercase mb-0.5">Localização Exata</p>
                        <p className="text-sm font-medium text-stone-800">{item.location}</p>
                      </div>
                    </div>

                    <div className="mt-auto pt-4 border-t border-stone-100 flex items-center justify-between">
                      {/* Status de Quantidade */}
                      <div>
                        <p className="text-xs text-stone-500 font-medium">Qtd. Atual</p>
                        <p className={`text-3xl font-black ${isLowStock ? 'text-red-600' : 'text-stone-800'}`}>
                          {item.qty}
                          <span className="text-sm font-normal text-stone-400 ml-1">/ mín {item.minQty}</span>
                        </p>
                      </div>

                      {/* Botões de Entrada / Saída */}
                      <div className="flex gap-2">
                        <button
                          onClick={() => handleOpenModal(item, 'remove')}
                          className="w-12 h-12 bg-red-100 text-red-700 rounded-xl flex items-center justify-center hover:bg-red-200 active:bg-red-300 transition-colors shadow-sm"
                          title="Retirar do estoque"
                        >
                          <Minus className="w-6 h-6 stroke-[3]" />
                        </button>
                        <button
                          onClick={() => handleOpenModal(item, 'add')}
                          className="w-12 h-12 bg-green-100 text-green-700 rounded-xl flex items-center justify-center hover:bg-green-200 active:bg-green-300 transition-colors shadow-sm"
                          title="Adicionar ao estoque"
                        >
                          <Plus className="w-6 h-6 stroke-[3]" />
                        </button>
                      </div>
                    </div>
                  </div>
                );
              })}
            </div>
          )}
        </section>
      </main>

      {}
      {modalState.isOpen && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-stone-900/60 backdrop-blur-sm">
          <div className="bg-white rounded-3xl shadow-2xl w-full max-w-md overflow-hidden animate-in fade-in zoom-in-95 duration-200">
            {/* Modal Header */}
            <div className={`p-6 text-white ${modalState.actionType === 'add' ? 'bg-green-600' : 'bg-red-500'}`}>
              <div className="flex justify-between items-start mb-2">
                <h3 className="text-2xl font-bold">
                  {modalState.actionType === 'add' ? 'Entrada de Material' : 'Retirada de Material'}
                </h3>
                <button 
                  onClick={() => setModalState(prev => ({ ...prev, isOpen: false }))}
                  className="text-white/80 hover:text-white bg-white/20 p-1 rounded-full transition-colors"
                >
                  <X className="w-5 h-5" />
                </button>
              </div>
              <p className="text-white/90 font-medium">
                {modalState.item?.name} <span className="text-white/70 text-sm">({modalState.item?.sku})</span>
              </p>
            </div>

            {/* Modal Body */}
            <form onSubmit={handleConfirmMovement} className="p-6">
              
              <div className="mb-5">
                <label className="block text-sm font-bold text-stone-700 mb-2">Quantidade a {modalState.actionType === 'add' ? 'Adicionar' : 'Retirar'}</label>
                <div className="flex items-center gap-4">
                  <button 
                    type="button"
                    onClick={() => setModalState(prev => ({ ...prev, quantity: Math.max(1, prev.quantity - 1) }))}
                    className="w-12 h-12 rounded-xl bg-stone-100 border border-stone-200 flex items-center justify-center hover:bg-stone-200"
                  >
                    <Minus className="w-5 h-5 text-stone-600" />
                  </button>
                  <input 
                    type="number"
                    min="1"
                    required
                    className="flex-1 text-center text-3xl font-bold text-stone-800 border-none focus:ring-0 p-0"
                    value={modalState.quantity}
                    onChange={(e) => setModalState(prev => ({ ...prev, quantity: parseInt(e.target.value) || 1 }))}
                  />
                  <button 
                    type="button"
                    onClick={() => setModalState(prev => ({ ...prev, quantity: prev.quantity + 1 }))}
                    className="w-12 h-12 rounded-xl bg-stone-100 border border-stone-200 flex items-center justify-center hover:bg-stone-200"
                  >
                    <Plus className="w-5 h-5 text-stone-600" />
                  </button>
                </div>
              </div>

              <div className="mb-8">
                <label className="block text-sm font-bold text-stone-700 mb-2 flex items-center gap-2">
                  <User className="w-4 h-4" /> Nome do Responsável
                </label>
                <input 
                  type="text" 
                  required
                  autoFocus
                  placeholder="Ex: João Silva"
                  className="w-full p-4 bg-stone-50 border-2 border-stone-200 rounded-xl text-lg focus:border-green-500 focus:ring-4 focus:ring-green-100 transition-all"
                  value={modalState.operatorName}
                  onChange={(e) => setModalState(prev => ({ ...prev, operatorName: e.target.value }))}
                />
              </div>

              <div className="flex gap-3">
                <button
                  type="button"
                  onClick={() => setModalState(prev => ({ ...prev, isOpen: false }))}
                  className="flex-1 py-4 font-bold text-stone-600 bg-stone-100 hover:bg-stone-200 rounded-xl transition-colors"
                >
                  Cancelar
                </button>
                <button
                  type="submit"
                  className={`flex-1 py-4 font-bold text-white rounded-xl transition-colors flex items-center justify-center gap-2
                    ${modalState.actionType === 'add' 
                      ? 'bg-green-600 hover:bg-green-700' 
                      : 'bg-red-500 hover:bg-red-600'
                    }
                  `}
                >
                  <Check className="w-5 h-5 stroke-[3]" />
                  Confirmar
                </button>
              </div>
            </form>
          </div>
        </div>
      )}

    </div>
  );
}