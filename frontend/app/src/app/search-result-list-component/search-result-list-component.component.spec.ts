import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { SearchResultListComponentComponent } from './search-result-list-component.component';

describe('SearchResultListComponentComponent', () => {
  let component: SearchResultListComponentComponent;
  let fixture: ComponentFixture<SearchResultListComponentComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ SearchResultListComponentComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(SearchResultListComponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should be created', () => {
    expect(component).toBeTruthy();
  });
});
